/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 00:26:32 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 00:27:01 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** data->ray.f_xwall = (double)(data->perso.pos.x +
**								(double)data->ray.cur_dist[y] * data->ray.dirx);
**	data->ray.f_ywall = (double)(data->perso.pos.y +
**								(double)data->ray.cur_dist[y] * data->ray.diry);
**	data->ray.cur_floorx = data->ray.f_xwall - (int)data->ray.f_xwall;
**	data->ray.cur_floory = data->ray.f_ywall - (int)data->ray.f_ywall;
**	data->ray.f_texx = (int)(data->ray.cur_floorx * data->sol.width);
**	data->ray.f_texy = (int)(data->ray.cur_floory * data->sol.height);
*/

void	draw_ground(t_data *data, int x, int y, double ratio)
{
	data->ray.f_texx = (int)(((double)(data->perso.pos.x +
(double)data->ray.cur_dist[y] * data->ray.dirx) - (int)((double)(
data->perso.pos.x + (double)data->ray.cur_dist[y] * data->ray.dirx))) *
data->sol.width);
	data->ray.f_texy = (int)(((double)(data->perso.pos.y +
(double)data->ray.cur_dist[y] * data->ray.diry) - (int)((double)(
data->perso.pos.y + (double)data->ray.cur_dist[y] * data->ray.diry))) *
data->sol.height);
	data->img.buffer[x + (y * (data->img.width))] =
	ground_dark(data->sol.buffer[abs((int)(data->sol.width *
		data->ray.f_texy + data->ray.f_texx))], ratio);
}

/*
** data->ray.f_xwall = (double)(data->perso.pos.x +
**								(double)data->ray.cur_dist[y] * data->ray.dirx);
**	data->ray.f_ywall = (double)(data->perso.pos.y +
**								(double)data->ray.cur_dist[y] * data->ray.diry);
**	data->ray.cur_floorx = data->ray.f_xwall - (int)data->ray.f_xwall;
**	data->ray.cur_floory = data->ray.f_ywall - (int)data->ray.f_ywall;
**	data->ray.f_texx = (int)(data->ray.cur_floorx * data->plafond.width);
**	data->ray.f_texy = (int)(data->ray.cur_floory * data->plafond.height);
*/

void	draw_sky(t_data *data, int x, int y, double ratio)
{
	data->ray.f_texx = (int)(((double)(data->perso.pos.x +
(double)data->ray.cur_dist[y] * data->ray.dirx) - (int)((double)(
data->perso.pos.x + (double)data->ray.cur_dist[y] * data->ray.dirx))) *
data->plafond.width);
	data->ray.f_texy = (int)(((double)(data->perso.pos.y +
(double)data->ray.cur_dist[y] * data->ray.diry) - (int)((double)(
data->perso.pos.y + (double)data->ray.cur_dist[y] * data->ray.diry))) *
data->plafond.height);
	data->img.buffer[x + (y * (data->img.width))] =
	ground_dark(data->plafond.buffer[abs((int)(data->plafond.width *
		data->ray.f_texy + data->ray.f_texx))], ratio);
}
