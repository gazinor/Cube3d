/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 21:07:22 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/05 21:10:02 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting(t_data *data, int x)
{
	raycast_value(data, x);
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltax;
			data->ray.mapx += data->ray.stepx;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sidedisty += data->ray.deltay;
			data->ray.mapy += data->ray.stepy;
			data->ray.side = 1;
		}
		if (data->map[data->ray.mapx][data->ray.mapy] > '0')
			data->ray.hit = 1;
	}
	wall_dist(data);
}

void	raycast_value(t_data *data, int x)
{
	init_ray(data, x);
	if (data->ray.dirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (
				data->perso.pos.x - data->ray.mapx) * data->ray.deltax;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (
				data->ray.mapx + 1.0 - data->perso.pos.x) * data->ray.deltax;
	}
	if (data->ray.diry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (
				data->perso.pos.y - data->ray.mapy) * data->ray.deltay;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (
				data->ray.mapy + 1.0 - data->perso.pos.y) * data->ray.deltay;
	}
}

void	wall_dist(t_data *data)
{
	int heightline;

	if (data->ray.side == 0)
		data->ray.walldist = ABS((data->ray.mapx - data->perso.pos.x +
					(1 - data->ray.stepx) / 2) / data->ray.dirx);
	else
		data->ray.walldist = ABS((data->ray.mapy - data->perso.pos.y + (
						1 - data->ray.stepy) / 2) / data->ray.diry);
	heightline = HEIGHT / data->ray.walldist;
	data->ray.start = (int)(-(heightline / 2) + HEIGHT / 2);
	data->ray.end = (int)((heightline / 2) + HEIGHT / 2);
	if (data->ray.start < 0)
		data->ray.start = 0;
	if (data->ray.end >= HEIGHT)
		data->ray.end = HEIGHT - 1;
}
