/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:26:00 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 07:25:41 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_option(t_data *data)
{
	load_image(data, &data->on_button, data->w / 5, data->h / 12);
	load_image(data, &data->off_button, data->w / 5, data->h / 12);
	load_image(data, &data->retour_s, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->retour_uns, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->mode_bonus, data->w / 3., data->h / 8);
}

int		option_key(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
		data->i_menu.ptr, 0, 0);
	put_img_to_win_coord(data, data->mode_bonus.ptr,
data->w / 5, 6 * data->h / 12 - (data->h / 12.) - (data->on_button.height / 4));
	if (data->option.status == 1)
		put_img_to_win_coord(data, data->on_button.ptr,
	data->w / 2 + (data->w / 7), 6 * data->h / 12 - (data->h / 12.));
	else
		put_img_to_win_coord(data, data->off_button.ptr,
	data->w / 2 + (data->w / 7), 6 * data->h / 12 - (data->h / 12.));
	if (data->option.button[1] == 1)
		put_img_to_win_coord(data, data->retour_s.ptr,
	data->w / 2 - (data->w / 3.6), data->h / 2 + data->h / 5.);
	else
		put_img_to_win_coord(data, data->retour_uns.ptr,
	data->w / 2 - (data->w / 3.6), data->h / 2 + data->h / 5.);
	return (0);
}

void	deal_enter_n_esc(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(data, FALSE, NULL);
	if (key == ENTER)
		if (data->option.i == 1)
		{
			data->event.option = 0;
			mlx_clear_window(data->mlx.ptr, data->mlx.win);
			menu(data);
		}
}

int		key_on_option(int key, t_data *data)
{
	deal_enter_n_esc(key, data);
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
	option_key(data);
	return (0);
}

void	option(t_data *data)
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
