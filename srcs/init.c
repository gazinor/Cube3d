/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:49 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/04 22:23:49 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_ray(t_data *data, int x)
{
	data->ray.start = 0;
	data->ray.end = 0;
	data->ray.camera = (2 * x / (double)WIDTH) - 1;
	data->ray.dirx = data->perso.dir.x + data->perso.planx * data->ray.camera;
	data->ray.diry = data->perso.dir.y + data->perso.plany * data->ray.camera;
	data->cast.mapx = (int)data->perso.pos.x;
	data->cast.mapy = (int)data->perso.pos.y;
	data->cast.sidedistx = 0;
	data->cast.sidedisty = 0;
	data->cast.deltax = sqrt(1 + ((data->ray.diry * data->ray.diry) /
				(data->ray.dirx * data->ray.dirx)));
	data->cast.deltay = sqrt(1 + ((data->ray.dirx * data->ray.dirx) /
				(data->ray.diry * data->ray.diry)));
	data->cast.stepx = 0;
	data->cast.stepy = 0;
	data->cast.hit = 0;
	data->cast.side = 0;
	data->cast.walldist = 0;
}

void    ft_init(t_data *data)
{
	data->perso.pos.x = 0;
	data->perso.pos.y = 0;
	data->perso.dir.x = 1;
	data->perso.dir.y = 0;
	data->perso.speed = 0.036;
	data->perso.rot = 2 * M_PI / 180;
	data->perso.plane = 70 / WIDTH;
	data->event.forward = 0;
	data->event.backward = 0;
	data->event.left = 0;
	data->event.right = 0;
	data->event.l_arrow = 0;
	data->event.r_arrow = 0;
	data->perso.planx = 0;
	data->perso.plany = 0.666;
	ft_init_map(data);
}
