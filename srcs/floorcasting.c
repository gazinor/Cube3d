/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 00:26:32 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/07 13:38:08 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	draw_skynground(t_data *data, int x, t_bool sol, int y)
{
	if (sol == TRUE)
	{
		data->ray.cur_dist = HEIGHT / (2.0 * y - HEIGHT);
		data->ray.f_xwall = (double)(data->perso.pos.x + (double)data->ray.cur_dist * data->ray.dirx);
		data->ray.f_ywall = (double)(data->perso.pos.y + (double)data->ray.cur_dist * data->ray.diry);
		data->ray.cur_floorx = (double)data->ray.f_xwall - floor(data->ray.f_xwall);
		data->ray.cur_floory = (double)data->ray.f_ywall - floor(data->ray.f_ywall);
		data->ray.f_texx = (int)(data->ray.cur_floorx * data->etext.width) % data->etext.width;
		data->ray.f_texy = (int)(data->ray.cur_floory * data->etext.height) % data->etext.height;
		data->img.buffer[x + (y * (data->img.width))] =
			ground_dark(data->etext.buffer[(int)(data->etext.width * data->ray.f_texy + data->ray.f_texx)],
					(HEIGHT - y) / (data->mod.nbr[DARK] == 1 ? 2 : 1) * data->calc.lum);
	}
	else
	{
		data->ray.cur_dist = HEIGHT / (HEIGHT - 2.0 * y);
		data->ray.f_xwall = (double)(data->perso.pos.x + (double)data->ray.cur_dist * data->ray.dirx);
		data->ray.f_ywall = (double)(data->perso.pos.y + (double)data->ray.cur_dist * data->ray.diry);
		data->ray.cur_floorx = (double)data->ray.f_xwall - floor(data->ray.f_xwall);
		data->ray.cur_floory = (double)data->ray.f_ywall - floor(data->ray.f_ywall);
		data->ray.f_texx = (int)(data->ray.cur_floorx * data->sol.width) % data->sol.width;
		data->ray.f_texy = (int)(data->ray.cur_floory * data->sol.height) % data->sol.height;
		data->img.buffer[x + (y * (data->img.width))] =
			ground_dark(data->sol.buffer[(int)(data->sol.width * data->ray.f_texy + data->ray.f_texx)],
					y * (data->mod.nbr[DARK] == 1 ? 0.5 : 1) * data->calc.lum);
	}
}
