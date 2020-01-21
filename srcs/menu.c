/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 21:08:23 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/21 06:56:40 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_menu(t_data *data)
{
	load_image(data, &data->i_menu, WIDTH, HEIGHT);
	load_image(data, &data->play_s_contour, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->option_s_contour, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->quit_s_contour, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->play_uns_contour, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->option_uns_contour, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->quit_uns_contour, WIDTH / 1.8, HEIGHT / 6.5);
}

int		menu_key(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->i_menu.ptr, 0, 0);
	if (data->menu.button[0] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->play_s_contour.ptr, WIDTH / 2 - (WIDTH / 3.6), 5 * HEIGHT / 12 - (HEIGHT / 12.));
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->play_uns_contour.ptr, WIDTH / 2 - (WIDTH / 3.6), 5 * HEIGHT / 12 - (HEIGHT / 12.));
	if (data->menu.button[1] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->option_s_contour.ptr, WIDTH / 2 - (WIDTH / 3.6), HEIGHT / 2 + HEIGHT / 18.);
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->option_uns_contour.ptr, WIDTH / 2 - (WIDTH / 3.6), HEIGHT / 2 + HEIGHT / 18.);
	if (data->menu.button[2] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->quit_s_contour.ptr, WIDTH / 2 - (WIDTH / 3.6), HEIGHT - (HEIGHT / 3.5) + HEIGHT / 18.);
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->quit_uns_contour.ptr, WIDTH / 2 - (WIDTH / 3.6), HEIGHT - (HEIGHT / 3.5) + HEIGHT / 18.);
	return (0);
}

int		key_on_menu(int key, t_data *data)
{
	if (data->event.option == 1)
		return (0);
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
		else if (data->menu.i == 1)
			option(data);
		else if (data->menu.i == 2)
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
	menu_key(data);
	mlx_do_key_autorepeatoff(data->mlx.ptr);
	mlx_hook(data->mlx.win, KEYDOWN, 0, key_on_menu, data);
	mlx_hook(data->mlx.win, QUIT, 0, exit_properly, data);
	mlx_loop(data->mlx.ptr);
}
