/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:29:11 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 03:44:11 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player2(t_data *data, char buf[4097])
{
	static int	x = 0;
	static int	x_ = 0;
	static int	y = 0;
	static int	y_ = 0;
	int			i;

	i = 0;
	while (!ft_isdigit(buf[i]))
		++i;
	x = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	x_ = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	y = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	y_ = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	i = atoi(buf + i);
	if (i > 0)
	{
		data->life.hurt += i;
		data->life.blood = 5;
	}
	pthread_mutex_lock(&data->mutex_player);
	create_obj(data, &data->player, data->player2[(int)data->player2_index], 0);
	data->player2_index = (int)(data->player2_index + 1) % NB_PLAYER2_IMG;
	data->player->sac.ray.mapx = x + x_ / 100. - 0.5;
	data->player->sac.ray.mapy = y + y_ / 100. - 0.5;
	data->player->sac.ray.walldist = sqrt((data->perso.pos.x - (x + x_ / 100.))
	* (data->perso.pos.x - (x + x_ / 100.)) + (data->perso.pos.y -
	(y + y_ / 100.)) * (data->perso.pos.y - (y + y_ / 100.)));
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
