/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:10:41 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 00:18:40 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	get_texture(t_data *data)
{
	if (data->ray.side == 1)
	{
		if (data->ray.stepy == -1)
			return (data->option.status == 1 ? data->ntext : data->parse.ntext);
		if (data->ray.stepy == 1)
			return (data->option.status == 1 ? data->stext : data->parse.stext);
	}
	if (data->ray.stepx == -1)
		return (data->option.status == 1 ? data->etext : data->parse.etext);
	return (data->option.status == 1 ? data->wtext : data->parse.wtext);
}

long	ground_dark(long color, double dist)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	dist = (7. / 100.) * dist > 0.9 ? 0.9 : (7. / 100.) * dist;
	if ((r = color) > 0)
		r = r - r * dist;
	if ((g = (color >> 8)) > 0)
		g = g - g * dist;
	if ((b = (color >> 16)) > 0)
		b = b - b * dist;
	return (r + (g << 8) + (b << 16));
}

void	init_calc(t_data *data, t_img texture)
{
	data->calc.calcx = ((data->ray.walldist * data->ray.dirx + data->perso.pos.x
			- (int)(data->ray.walldist * data->ray.dirx + data->perso.pos.x)) *
			texture.height);
	data->calc.calcy = ((data->ray.walldist * data->ray.diry + data->perso.pos.y
			- (int)(data->ray.walldist * data->ray.diry + data->perso.pos.y)) *
			texture.height);
	data->calc.ratio = (texture.height / (double)data->ray.heightline);
	data->img.width = data->img.size / 4;
	data->calc.lum = (24. / data->h * (data->mod.nbr[DARK] == 1 ? 3.8 : 1));
}
