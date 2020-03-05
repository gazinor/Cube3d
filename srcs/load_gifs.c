/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gifs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:09:23 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 04:19:07 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_portal(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_PORTAL_IMG)
		load_image(data, &data->portal[i], 1000, 1000);
}

void	load_sword(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_SWORD_IMG)
		load_image(data, &data->sword[i], data->w / 2, data->h);
}

void	load_you_died(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_YOU_DIED_IMG)
		load_image(data, &data->you_died[i], data->w, data->h / 2);
}

void	load_player2(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_PLAYER2_IMG)
		load_image(data, &data->player2[i], 1000, 1000);
}

void	load_door(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_DOOR_IMG)
		load_image(data, &data->gif_door[i], 1000, 1000);
}
