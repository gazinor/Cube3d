/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:29:11 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/10 00:37:13 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_digits(t_pos *nb, t_pos *floats, char buf[4097])
{
	int			i;

	i = 0;
	printf("buffer : |%s|\n", buf);
	if (!buf || !*buf)
		return (-1);
	while (buf[i] && !ft_isdigit(buf[i]))
		++i;
	nb->x = atoi(buf + i);
	while (buf[i] && ft_isdigit(buf[i]))
		++i;
	++i;
	floats->x = atoi(buf + i);
	while (buf[i] && ft_isdigit(buf[i]))
		++i;
	++i;
	nb->y = atoi(buf + i);
	while (buf[i] && ft_isdigit(buf[i]))
		++i;
	++i;
	floats->y = atoi(buf + i);
	while (buf[i] && ft_isdigit(buf[i]))
		++i;
	++i;
	return (i);
}

void	ft_player2(t_data *data, char buf[4097])
{
	static t_pos	nb;
	static t_pos	floats;
	int				i;

	i = get_digits(&nb, &floats, buf);
	i = atoi(buf + i);
	if (i > 0)
	{
		data->life.hurt += i;
		data->life.blood = 3;
	}
	pthread_mutex_lock(&data->mutex_player);
	create_obj(data, &data->player, data->player2[(int)data->player2_index], 0);
	data->player2_index = (int)(data->player2_index + 1) % NB_PLAYER2_IMG;
	data->player->sac.ray.mapx = nb.x + floats.x / 100. - 0.5;
	data->player->sac.ray.mapy = nb.y + floats.y / 100. - 0.5;
	data->player->sac.ray.walldist = sqrt((data->perso.pos.x -
				(nb.x + floats.x / 100.))
	* (data->perso.pos.x - (nb.x + floats.x / 100.)) + (data->perso.pos.y -
	(nb.y + floats.y / 100.)) * (data->perso.pos.y - (nb.y + floats.y / 100.)));
	pthread_mutex_unlock(&data->mutex_player);
}

void	*t_loop(void *arg)
{
	int		fd;
	char	buf[4097];
	int		ret;
	t_data	*data;

	fd = open("/dev/fd/0", O_RDONLY | O_NONBLOCK);
	data = (t_data *)arg;
	data->launch = FALSE;
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		buf[ret] = 0;
		if (!strncmp(buf, "open door", 9))
			data->door_index = 0;
		else
		{
			if (data->launch == TRUE)
				ft_player2(data, buf);
		}
	}
	return (NULL);
}

char	*serialized(t_data *data)
{
	char	*str;

	str = NULL;
	str = ft_strdup("echo \"");
	str = join_n_free(str, ft_itoa((int)data->perso.pos.x));
	str = join_n_free(str, ft_strdup(";"));
	str = join_n_free(str, ft_itoa((int)((data->perso.pos.x -
						(int)data->perso.pos.x) * 100)));
	str = join_n_free(str, ft_strdup(";"));
	str = join_n_free(str, ft_itoa((int)data->perso.pos.y));
	str = join_n_free(str, ft_strdup(";"));
	str = join_n_free(str, ft_itoa((int)((data->perso.pos.y -
						(int)data->perso.pos.y) * 100)));
	str = join_n_free(str, ft_strdup(";"));
	str = join_n_free(str, data->event.hit[0] == TRUE ?
			ft_itoa((int)data->life.hit) : 0);
	str = join_n_free(str, ft_strdup("\" | nc localhost 13000"));
	data->event.hit[0] = FALSE;
	return (str);
}
