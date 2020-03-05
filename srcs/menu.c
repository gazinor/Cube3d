/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 21:08:23 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 07:25:29 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		menu_key(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win,
			data->i_menu.ptr, 0, 0);
	if (data->menu.button[0] == 1)
		put_img_to_win_coord(data, data->play_s_contour.ptr,
			data->w / 2 - (data->w / 3.6), 5 * data->h / 12 - (data->h / 12.));
	else
		put_img_to_win_coord(data, data->play_uns_contour.ptr,
			data->w / 2 - (data->w / 3.6), 5 * data->h / 12 - (data->h / 12.));
	if (data->menu.button[1] == 1)
		put_img_to_win_coord(data, data->option_s_contour.ptr,
			data->w / 2 - (data->w / 3.6), data->h / 2 + data->h / 18.);
	else
		put_img_to_win_coord(data, data->option_uns_contour.ptr,
			data->w / 2 - (data->w / 3.6), data->h / 2 + data->h / 18.);
	if (data->menu.button[2] == 1)
		put_img_to_win_coord(data, data->quit_s_contour.ptr,
	data->w / 2 - (data->w / 3.6), data->h - (data->h / 3.5) + data->h / 18.);
	else
		put_img_to_win_coord(data, data->quit_uns_contour.ptr,
	data->w / 2 - (data->w / 3.6), data->h - (data->h / 3.5) + data->h / 18.);
	return (0);
}

char	**ft_tabdup(char **str)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	while (str[i])
		i++;
	if (!(dest = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		j = 0;
		if (!(dest[i] = malloc(sizeof(char) * (ft_strlen(str[i]) + 1))))
			return (NULL);
		while (str[i][j])
		{
			dest[i][j] = str[i][j];
			j++;
		}
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int		deal_enter(int key, t_data *data)
{
	if (key == ENTER)
	{
		if (data->menu.i == 0)
		{
			data->event.menu = 0;
			if (data->option.status == 1)
				data->launch = TRUE;
			else
				data->launch = FALSE;
			data->option.status == 1 ? init_bonus(data) : init_normale(data);
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
	deal_enter(key, data);
	return (0);
}

void	menu(t_data *data)
{
	ft_init_player(data);
	menu_key(data);
	mlx_do_key_autorepeatoff(data->mlx.ptr);
	mlx_hook(data->mlx.win, KEYDOWN, 0, key_on_menu, data);
	mlx_hook(data->mlx.win, QUIT, 0, exit_properly, data);
	mlx_loop(data->mlx.ptr);
}
