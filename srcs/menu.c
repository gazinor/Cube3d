/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 21:08:23 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/17 05:00:00 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_menu(t_data *data)
{
	data->i_menu.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/menu.xpm", &(data->i_menu.width), &(data->i_menu.height));
	data->tmp_menu = resize_image(data, &data->i_menu, WIDTH, HEIGHT);
	mlx_destroy_image(data->mlx.ptr, data->i_menu.ptr);
	data->i_menu = data->tmp_menu;
	data->s_contour.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/selected_contour.xpm", &(data->s_contour.width),
		&(data->s_contour.height));
	data->tmp_s_contour = resize_image(data, &data->s_contour, WIDTH / 3.3,
			HEIGHT / 3.5);
	mlx_destroy_image(data->mlx.ptr, data->s_contour.ptr);
	data->s_contour = data->tmp_s_contour;
	data->uns_contour.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/unselected_contour.xpm", &(data->uns_contour.width),
		&(data->uns_contour.height));
	data->tmp_uns_contour = resize_image(data, &data->uns_contour, WIDTH / 3.3,
			HEIGHT / 3.5);
	mlx_destroy_image(data->mlx.ptr, data->uns_contour.ptr);
	data->uns_contour = data->tmp_uns_contour;
}

int		menu_key(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->i_menu.ptr, 0, 0);
	if (data->menu.button[0] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->s_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), 5 * HEIGHT / 12 - (HEIGHT / 7.));
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->uns_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), 5 * HEIGHT / 12 - (HEIGHT / 7.));
	if (data->menu.button[1] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->s_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), HEIGHT / 2);
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->uns_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), HEIGHT / 2);
	if (data->menu.button[2] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->s_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), HEIGHT - (HEIGHT / 3.5));
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->uns_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), HEIGHT - (HEIGHT / 3.5));
	return (0);
}

int		key_on_menu(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(data, FALSE, NULL);
	if (key == U_ARROW)
	{
		data->menu.button[data->menu.i] ^= 1;
		if (--data->menu.i <= -1)
			data->menu.i = 2;
		data->menu.button[data->menu.i] ^= 1;
	}
	if (key == D_ARROW)
	{
		data->menu.button[data->menu.i] ^= 1;
		if (++data->menu.i >= 3)
			data->menu.i = 0;
		data->menu.button[data->menu.i] ^= 1;
	}
	if (key == ENTER)
	{
		if (data->menu.i == 0)
		{
			data->event.menu = 0;
			mlx_clear_window(data->mlx.ptr, data->mlx.win);
			loop(data);
		}
//		if (data->menu.i == 1)
//			option(data);
		if (data->menu.i == 2)
			exit_properly(data, 0, NULL);
	}
	menu_key(data);
	return (0);
}

void	menu(t_data *data)
{
	data->menu.button[0] = 1;
	data->menu.button[1] = 0;
	data->menu.button[2] = 0;
	data->menu.i = 0;
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->i_menu.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
	data->s_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), 5 * HEIGHT / 12 - (HEIGHT / 7.));
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
	data->uns_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), HEIGHT / 2);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
	data->uns_contour.ptr, WIDTH / 2 - (WIDTH / 6.3), HEIGHT - (HEIGHT / 3.5));
	mlx_do_key_autorepeatoff(data->mlx.ptr);
	mlx_hook(data->mlx.win, KEYDOWN, 0, key_on_menu, data);
	mlx_hook(data->mlx.win, QUIT, 0, exit_properly, data);
	mlx_loop(data->mlx.ptr);
}
