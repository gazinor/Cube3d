/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 05:15:49 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 05:31:13 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	launch_program(t_data *data, int ac, char **av)
{
	pthread_t	thread;
	pthread_t	download;
	pthread_t	monster;
	pthread_t	tp;

	if (ac != 3 && ac != 2)
	{
		write(2, "\e[31mErreur\n", 12);
		write(2, "Mauvais nombre d'arguments.\n", 28);
		exit(0);
	}
	ft_init(data);
	data->launch = FALSE;
	data->mlx.ptr = mlx_init();
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.size, &data->img.endian);
	pthread_mutex_init(&data->mutex_player, NULL);
	pthread_create(&download, NULL, draw_downloading, data);
	pthread_create(&thread, NULL, t_loop, data);
	pthread_create(&tp, NULL, do_tp, data);
	pthread_create(&monster, NULL, use_monsters, data);
	parsing(av[1], data);
}
