/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 03:27:51 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 10:24:46 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*draw_downloading(void *arg)
{
	int		i;
	int		j;
	char	*str;
	t_data	*data;

	data = (t_data *)arg;
	write(1, "\n\n\n\n", 4);
	i = 0;
	while (i < 81)
	{
		j = -1;
		write(1, "\e[1;4;38;5;123m", 15);
		write(1, (str = ft_itoa(i * 1.25)), 1 + ((i * 1.25 < 100) ? 1 : 2));
		write(1, "%\e[0m \e[48;5;52m", 16);
		while (++j < i)
			write(1, "\e[0;107m ", 10);
		write(1, "\e[48;5;52m", 11);
		while (++j < 81)
			write(1, " ", 1);
		write(1, "\e[0m", 5);
		fflush(stdout);
		usleep(30000);
		write(1, "\r", 1);
		i = (int)data->download_percent;
		free(str);
	}
	return (NULL);
}

void	launch_tp(t_data *data, double *x, double *y)
{
	if (data->launch == TRUE)
	{
		pthread_mutex_lock(&data->mutex_player);
		if (!data->tp_lst)
			create_obj(data, &data->tp_lst, data->tp[
					(int)data->tp_index % NB_TP], 0);
		data->tp_index += 0.0000004;
		data->tp_lst->sac.img = data->tp[(int)data->tp_index % NB_TP];
		data->tp_lst->sac.ray.mapx = *x;
		data->tp_lst->sac.ray.mapy = *y;
		data->tp_lst->sac.ray.walldist = sqrt((data->perso.pos.x - 0.5 - *x)
			* (data->perso.pos.x - 0.5 - *x) + (data->perso.pos.y - 0.5 - *y)
			* (data->perso.pos.y - 0.5 - *y));
		pthread_mutex_unlock(&data->mutex_player);
	}
}

void	*do_tp(void *arg)
{
	t_data	*data;
	double	x;
	double	y;
	int		life;

	data = (t_data *)arg;
	x = 2.;
	y = 2.;
	life = 3;
	while (1)
	{
		launch_tp(data, &x, &y);
		if (data->event.hit[2] == TRUE && --life != -1)
			data->event.hit[2] = FALSE;
		if (life <= 0)
		{
			free(data->tp_lst);
			data->tp_lst = NULL;
			data->tp_index = -1;
			break ;
		}
	}
	return (NULL);
}
