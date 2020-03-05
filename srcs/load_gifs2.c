/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gifs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:11:24 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 05:31:44 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_screamer(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NB_SCREAMER_IMG)
		load_image(data, &data->screamer[i], data->w, data->h);
}

void	load_monster(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NB_MONSTER_IMG)
		load_image(data, &data->monster[i], 1000, 1000);
}

void	load_tp(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NB_TP)
		load_image(data, &data->tp[i], 1000, 1000);
}

void	load_all(t_data *data)
{
	load_background(data);
	load_dir_textures(data);
	load_objs(data);
	load_portal(data);
	load_sword(data);
	load_you_died(data);
	load_player2(data);
	load_screamer(data);
	load_monster(data);
	load_tp(data);
	load_door(data);
	load_menu(data);
	load_option(data);
}
