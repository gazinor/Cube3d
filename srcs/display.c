/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/05 02:21:12 by gaefourn         ###   ########.fr       */
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

long		get_texture(t_data *data)
{
	if (data->ray.side == 1)
	{
		if (data->ray.stepy == -1)
			return (0xFF0000);
		if (data->ray.stepy == 1)
			return (0x0000FF);
	}
	if (data->ray.stepx == -1)
		return (0xFFFFFF);
	return (0xEFD807);
}

void        crt_column(t_data *data, int column)
{
	int i;
	long color;

	i = -1;
	color = get_texture(data);
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFFFF;
	i--;
	while (++i < data->ray.end)
		data->img.buffer[column + (i * (data->img.size / 4))] = color;
	i--;
	while (++i < HEIGHT)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xA0AAAAAA;
}

void    raycasting(t_data *data, int x)
{
	raycast_value(data, x);
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltax;
			data->ray.mapx += data->ray.stepx;
			data->ray.side = 0; //Nord sud
		}
		else
		{
			data->ray.sidedisty += data->ray.deltay;
			data->ray.mapy += data->ray.stepy;
			data->ray.side = 1; //Est ouest
		}
		if (data->map[data->ray.mapx][data->ray.mapy] > '0')
			data->ray.hit = 1;
	}
	wall_dist(data);
}

void    raycast_value(t_data *data, int x)
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

void    wall_dist(t_data *data)
{
	int heightline;

	if (data->ray.side == 0)
		data->ray.walldist = ABS((data->ray.mapx - data->perso.pos.x + (
						1 - data->ray.stepx)/2) / data->ray.dirx);
	else
		data->ray.walldist = ABS((data->ray.mapy - data->perso.pos.y + (
						1 - data->ray.stepy)/2) / data->ray.diry);
	heightline = HEIGHT / data->ray.walldist;
	data->ray.start = (int)(-(heightline / 2) + HEIGHT / 2);
	data->ray.end = (int)((heightline / 2) + HEIGHT / 2);
	if (data->ray.start < 0)
		data->ray.start = 0;
	if (data->ray.end >= HEIGHT)
		data->ray.end = HEIGHT - 1;
}
