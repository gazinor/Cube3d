/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 05:15:49 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/09 11:48:20 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	launch_program(t_data *data, int ac, char **av)
{
	if (ac != 3 && ac != 2)
	{
		write(2, "\e[31mErreur\n", 12);
		write(2, "Mauvais nombre d'arguments.\n", 28);
		exit(0);
	}
	data->mlx.ptr = mlx_init();
	ft_init2(data);
	data->begin = FALSE;
	parsing(av[1], data);
	ft_init(data);
	data->launch = FALSE;
	data->img.ptr = mlx_new_image(data->mlx.ptr, data->w, data->h);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.size, &data->img.endian);
	pthread_mutex_init(&data->mutex_player, NULL);
	pthread_create(&data->t_download, NULL, draw_downloading, data);
	pthread_create(&data->t_thread, NULL, t_loop, data);
	pthread_create(&data->t_tp, NULL, do_tp, data);
	pthread_create(&data->t_monster, NULL, use_monsters, data);
}
