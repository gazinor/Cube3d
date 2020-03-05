/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 21:07:22 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 06:15:24 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_portal(t_data *data, double new_x, double new_y)
{
	if (data->map[(int)new_x][(int)new_y] == 'P' ||
		data->map[(int)new_x][(int)new_y] == 'O' ||
		data->map[(int)new_x][(int)new_y] == 'R' ||
		data->map[(int)new_x][(int)new_y] == 'T' ||
		data->map[(int)new_x][(int)new_y] == 'A' ||
		data->map[(int)new_x][(int)new_y] == 'L')
		return (TRUE);
	return (FALSE);
}

void	check_wall_type(t_data *data, int x)
{
	if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '1' ||
			data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '3')
		data->ray.hit = 1;
	wall_dist(data);
	data->zbuffer[x] = data->ray.walldist;
	if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '4' ||
		data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '5')
	{
		if (!data->event.door)
			data->ray.hit = 1;
		create_door(data, &data->door, x);
	}
	else if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '2')
		create_obj(data, &data->obj, data->sprite, 0);
	else if (check_portal(data, data->ray.mapx, data->ray.mapy) == TRUE)
		create_portal(data, &data->portal_lst);
	else if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] == 'x')
		create_obj(data, &data->obj, data->spikes,
			data->ray.heightline * 0.25);
}

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
		if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] > '0')
			check_wall_type(data, x);
	}
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
	if (data->ray.side == 0)
		data->ray.walldist = my_abs((data->ray.mapx - data->perso.pos.x +
					(1 - data->ray.stepx) / 2) / data->ray.dirx);
	else
		data->ray.walldist = my_abs((data->ray.mapy - data->perso.pos.y + (
						1 - data->ray.stepy) / 2) / data->ray.diry);
	data->ray.heightline = data->h / data->ray.walldist;
	data->ray.start = (int)(-(data->ray.heightline / 2) + data->h / 2);
	data->ray.end = (int)((data->ray.heightline / 2) + data->h / 2);
	data->ray.truestart = (int)(-(data->ray.heightline / 2) + data->h / 2);
	data->ray.trueend = (int)((data->ray.heightline / 2) + data->h / 2);
	if (data->ray.start < 0)
		data->ray.start = 0;
	if (data->ray.end >= data->h)
		data->ray.end = data->h - 1;
}
