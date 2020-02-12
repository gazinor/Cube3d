/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 00:26:32 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/12 03:24:19 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	draw_skynground(t_data *data, int x, t_bool sol, int y)
{
	if (sol == TRUE)
	{
		data->ray.f_xwall = (double)(data->perso.pos.x + (double)data->ray.cur_dist[y] * data->ray.dirx);
		data->ray.f_ywall = (double)(data->perso.pos.y + (double)data->ray.cur_dist[y] * data->ray.diry);
		data->ray.cur_floorx = data->ray.f_xwall - (int)data->ray.f_xwall;
		data->ray.cur_floory = data->ray.f_ywall - (int)data->ray.f_ywall;
		data->ray.f_texx = (int)(data->ray.cur_floorx * data->sol.width);
		data->ray.f_texy = (int)(data->ray.cur_floory * data->sol.height);
		data->img.buffer[x + (y * (data->img.width))] =
		ground_dark(data->sol.buffer[abs((int)(data->sol.width * data->ray.f_texy + data->ray.f_texx))],
					(HEIGHT - y) * (data->mod.nbr[DARK] == 1 ? 0.5 : 1) * data->calc.lum);
	}
	else
	{
		data->ray.f_xwall = (double)(data->perso.pos.x + (double)data->ray.cur_dist[y] * data->ray.dirx);
		data->ray.f_ywall = (double)(data->perso.pos.y + (double)data->ray.cur_dist[y] * data->ray.diry);
		data->ray.cur_floorx = data->ray.f_xwall - (int)data->ray.f_xwall;
		data->ray.cur_floory = data->ray.f_ywall - (int)data->ray.f_ywall;
		data->ray.f_texx = (int)(data->ray.cur_floorx * data->plafond.width);
		data->ray.f_texy = (int)(data->ray.cur_floory * data->plafond.height);
		data->img.buffer[x + (y * (data->img.width))] =
		ground_dark(data->plafond.buffer[abs((int)(data->plafond.width * data->ray.f_texy + data->ray.f_texx))],
					y * (data->mod.nbr[DARK] == 1 ? 0.5 : 1) * data->calc.lum);
	}
}
