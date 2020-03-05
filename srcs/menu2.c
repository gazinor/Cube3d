/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 23:40:20 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 11:23:35 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_bonus(t_data *data)
{
	int		i;

	i = -1;
	if (data->map)
	{
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
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
	int		i;

	i = -1;
	if (data->map)
	{
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
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

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void	load_menu(t_data *data)
{
	load_image(data, &data->i_menu, data->w, data->h);
	load_image(data, &data->play_s_contour, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->option_s_contour, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->quit_s_contour, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->play_uns_contour, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->option_uns_contour, data->w / 1.8, data->h / 6.5);
	load_image(data, &data->quit_uns_contour, data->w / 1.8, data->h / 6.5);
}

void	put_img_to_win_coord(t_data *data, void *ptr, int x, int y)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, ptr, x, y);
}
