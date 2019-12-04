/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/04 22:19:14 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int		exit_properly(t_bool error, char *error_msg)
{
	int		i;

	i = 0;
	if (error == TRUE)
	{
		while (error_msg[i])
			++i;
		write(2, error_msg, i);
		exit(1);
	}
	exit(0);
}

int			key(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(FALSE, NULL);
	else if (key == FORWARD)
        data->event.forward ^= 1;
    else if (key == BACKWARD)
        data->event.backward ^= 1;
    else if (key == RIGHT)
        data->event.right ^= 1;
    else if (key == LEFT)
        data->event.left ^= 1;
    else if (key == R_ARROW)
        data->event.r_arrow ^= 1;
    else if (key == L_ARROW)
        data->event.l_arrow ^= 1;
	return (0);
}

int     ft_move(t_data *data)
{
    if (data->event.forward == 1)
		move_forward(data);
	if (data->event.backward == 1)
		move_backward(data);
    if (data->event.right == 1)
		move_right(data);
    if (data->event.left == 1)
		move_left(data);
    if (data->event.r_arrow == 1)
		turn_right(data);
    if (data->event.l_arrow == 1)
		turn_left(data);
	crt_img(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
    return (0);
}

int		main()
{
	t_data	data;

	ft_init(&data);
	data.mlx.ptr = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.ptr, WIDTH, HEIGHT, "Cube3d");
	data.img.ptr = mlx_new_image(data.mlx.ptr, WIDTH, HEIGHT);
	data.img.buffer = (int*)mlx_get_data_addr(data.img.ptr, &data.img.bpp,
										&data.img.size, &data.img.endian);
	mlx_do_key_autorepeatoff(data.mlx.ptr);
	mlx_hook(data.mlx.win, KEYDOWN, 0, key, &data);
	mlx_hook(data.mlx.win, KEYUP, 0, key, &data);
	mlx_hook(data.mlx.win, QUIT, 0, exit_properly, &data);
	mlx_loop_hook(data.mlx.ptr, ft_move, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
