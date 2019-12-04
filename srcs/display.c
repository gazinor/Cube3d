/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/04 22:21:00 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        *crt_img(t_data *data)
{
	int x;

	x = -1;
	while (++x < WIDTH)
	{
		raycasting(data, x);
		crt_column(data, x);
	}
	return (data->img.buffer);
}

void        crt_column(t_data *data, int column)
{
	int i;

	i = -1;
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFFFF;
	i--;
	while (++i < data->ray.end)
	{
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFF0000;
	}
	i--;
	while (++i < HEIGHT)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xA0AAAAAA;
}

void    raycasting(t_data *data, int x)
{
	raycast_value(data, x);
	while (data->cast.hit == 0)
	{
		if (data->cast.sidedistx < data->cast.sidedisty)
		{
			data->cast.sidedistx += data->cast.deltax;
			data->cast.mapx += data->cast.stepx;
			data->cast.side = 0;
		}
		else
		{
			data->cast.sidedisty += data->cast.deltay;
			data->cast.mapy += data->cast.stepy;
			data->cast.side = 1;
		}
		if (data->map[data->cast.mapx][data->cast.mapy] > '0')
			data->cast.hit = 1;
	}
	wall_dist(data);
}

void    raycast_value(t_data *data, int x)
{
	init_ray(data, x);
	if (data->ray.dirx < 0)
	{
		data->cast.stepx = -1;
		data->cast.sidedistx = (
				data->perso.pos.x - data->cast.mapx) * data->cast.deltax;
	}
	else
	{
		data->cast.stepx = 1;
		data->cast.sidedistx = (
				data->cast.mapx + 1.0 - data->perso.pos.x) * data->cast.deltax;
	}
	if (data->ray.diry < 0)
	{
		data->cast.stepy = -1;
		data->cast.sidedisty = (
				data->perso.pos.y - data->cast.mapy) * data->cast.deltay;
	}
	else
	{
		data->cast.stepy = 1;
		data->cast.sidedisty = (
				data->cast.mapy + 1.0 - data->perso.pos.y) * data->cast.deltay;
	}
}

void    wall_dist(t_data *data)
{
	int heightline;

	if (data->cast.side == 0)
		data->cast.walldist = ABS((data->cast.mapx - data->perso.pos.x + (
						1 - data->cast.stepx)/2) / data->ray.dirx);
	else
		data->cast.walldist = ABS((data->cast.mapy - data->perso.pos.y + (
						1 - data->cast.stepy)/2) / data->ray.diry);
	heightline = HEIGHT / data->cast.walldist;
	data->ray.start = (int)(-(heightline / 2) + HEIGHT / 2);
	data->ray.end = (int)((heightline / 2) + HEIGHT / 2);
	if (data->ray.start < 0)
		data->ray.start = 0;
	if (data->ray.end >= HEIGHT)
		data->ray.end = HEIGHT - 1;
}
