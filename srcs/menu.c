/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 21:08:23 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/24 00:08:51 by glaurent         ###   ########.fr       */
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

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	**ft_tabdup(char **str)
{
	char    **dest;
	int     i;
	int     j;

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

void	init_bonus(t_data *data)
{
	if (data->map)
		free(data->map);
	data->map = ft_tabdup(data->bonus.map);
	data->perso.pos.x = data->bonus.pos.x;
	data->perso.pos.y = data->bonus.pos.y;
	data->perso.dir.x = data->bonus.dir.x;
	data->perso.dir.y = data->bonus.dir.y;
	data->perso.planx = data->bonus.planx;
	data->perso.plany = data->bonus.plany;
}

void	init_normale(t_data *data)
{
	if (data->map)
		free(data->map);
	data->map = ft_tabdup(data->parse.map);
	data->perso.pos.x = data->parse.pos.x;
	data->perso.pos.y = data->parse.pos.y;
	data->perso.pos.x = data->parse.pos.x;
	data->perso.pos.y = data->parse.pos.y;
	data->perso.dir.x = data->parse.dir.x;
	data->perso.dir.y = data->parse.dir.y;
	data->perso.planx = data->parse.planx;
	data->perso.plany = data->parse.plany;
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

void	menu(t_data *data)
{
	ft_init_player(data);
	menu_key(data);
	mlx_do_key_autorepeatoff(data->mlx.ptr);
	mlx_hook(data->mlx.win, KEYDOWN, 0, key_on_menu, data);
	mlx_hook(data->mlx.win, QUIT, 0, exit_properly, data);
	mlx_loop(data->mlx.ptr);
}
