/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gifs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:11:24 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 01:12:05 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    load_screamer(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_SCREAMER_IMG)
		load_image(data, &data->screamer[i], WIDTH, HEIGHT);
}

void    load_monster(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_MONSTER_IMG)
		load_image(data, &data->monster[i], 1000, 1000);
}

void    load_tp(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_TP)
		load_image(data, &data->tp[i], 1000, 1000);
}
