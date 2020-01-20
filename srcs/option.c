/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:26:00 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/20 08:27:33 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    load_option(t_data *data)
{
	load_image(data, &data->on_button, WIDTH / 5, HEIGHT / 12);
	load_image(data, &data->off_button, WIDTH / 5, HEIGHT / 12);
	load_image(data, &data->retour_s, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->retour_uns, WIDTH / 1.8, HEIGHT / 6.5);
	load_image(data, &data->mode_bonus, WIDTH / 3., HEIGHT / 8);
}

int     option_key(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->i_menu.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->mode_bonus.ptr, WIDTH / 5, 6 * HEIGHT / 12 - (HEIGHT / 12.) - (data->on_button.height / 4));
	if (data->option.status == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->on_button.ptr, WIDTH / 2 + (WIDTH / 7), 6 * HEIGHT / 12 - (HEIGHT / 12.));
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->off_button.ptr, WIDTH / 2 + (WIDTH / 7), 6 * HEIGHT / 12 - (HEIGHT / 12.));
	if (data->option.button[1] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->retour_s.ptr, WIDTH / 2 - (WIDTH / 3.6), HEIGHT / 2 + HEIGHT / 5.);
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
				data->retour_uns.ptr, WIDTH / 2 - (WIDTH / 3.6), HEIGHT / 2 + HEIGHT / 5.);
	return (0);
}

int     key_on_option(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(data, FALSE, NULL);
	if (key == U_ARROW)
	{
		data->option.button[data->option.i] ^= 1;
		if (--data->option.i <= -1)
			data->option.i = 1;
		data->option.button[data->option.i] ^= 1;
	}
	if (key == D_ARROW)
	{
		data->option.button[data->option.i] ^= 1;
		if (++data->option.i >= 2)
			data->option.i = 0;
		data->option.button[data->option.i] ^= 1;
	}
	if (data->option.button[0] == 1)
	{
		if (key == L_ARROW)
			data->option.status = 0;
		if (key == R_ARROW)
			data->option.status = 1;
	}
	if (key == ENTER)
	{
		if (data->option.i == 1)
		{
			data->event.option = 0;
			mlx_clear_window(data->mlx.ptr, data->mlx.win);
			menu(data);
		}
	}
	option_key(data);
	return (0);
}

void    option(t_data *data)
{
	data->option.button[0] = 1;
	data->option.button[1] = 0;
	data->option.i = 0;
	option_key(data);
	mlx_do_key_autorepeatoff(data->mlx.ptr);
	mlx_hook(data->mlx.win, KEYDOWN, 0, key_on_option, data);
	mlx_hook(data->mlx.win, QUIT, 0, exit_properly, data);
	mlx_loop(data->mlx.ptr);
}

