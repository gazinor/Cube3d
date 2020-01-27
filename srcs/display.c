/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/27 01:04:01 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*crt_img(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		raycasting(data, x);
		crt_column(data, x);
	}
	return (data->img.buffer);
}

t_img	get_texture(t_data *data)
{
	if (data->ray.side == 1)
	{
		if (data->ray.stepy == -1)
			return (data->option.status == 1 ?
				data->ntext : data->parse.ntext);
		if (data->ray.stepy == 1)
			return (data->option.status == 1 ?
				data->stext : data->parse.stext);
	}
	if (data->ray.stepx == -1)
		return (data->option.status == 1 ? data->etext : data->parse.etext);
	return (data->option.status == 1 ? data->wtext : data->parse.wtext);
}

long	ground_dark(long color, double dist)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	dist = (7. / 100.) * dist > 0.9 ? 0.9 : (7. / 100.) * dist;
	if ((r = color) > 0)
		r = r - r * dist;
	if ((g = (color >> 8)) > 0)
		g = g - g * dist;
	if ((b = (color >> 16)) > 0)
		b = b - b * dist;
	return(r + (g << 8) + (b << 16));	
}

void	crt_sky(t_data *data, int column)
{
	int		i;

	i = -1;
	data->calc.offset = (atan2(data->ray.dirx, data->ray.diry) + M_PI) *
		M_1_PI * .5;
	if (data->option.status == 1)
	{
		if (data->mod.nbr[DARK] == 1)
			while (++i < data->ray.start)
				data->img.buffer[column + (i * (data->img.width))] =
					data->ciel_etoile.buffer[(int)((data->calc.offset + i) *
							data->ciel_etoile.width)];
		else
			while (++i < data->ray.start)
				data->img.buffer[column + (i * (data->img.width))] =
		data->ciel.buffer[(int)((data->calc.offset + i) * data->ciel.width)];
	}
	else
		while (++i < data->ray.start)
			data->img.buffer[column + (i * (data->img.width))] =
						data->parse.c_color;
}

void	crt_ground(t_data *data, int column)
{
	int		i;

	i = data->ray.end - 1;
	if (data->option.status == 1)
		if (data->mod.nbr[MIRROR] == 1)
		{
			while (++i < HEIGHT && i < data->ray.end + data->ray.heightline)
				data->img.buffer[column + (i * (data->img.width))] =
ground_dark(data->img.buffer[column + ((data->ray.end - (i - data->ray.end)) *
					(data->img.width))], (HEIGHT - i) * data->calc.lum);
			--i;
			while (++i < HEIGHT)
				data->img.buffer[column + (i * (data->img.width))] =
ground_dark(data->img.buffer[column + (data->ray.end - (i - data->ray.end) -
data->ray.heightline) *	data->img.width], (HEIGHT - i) * data->calc.lum);
		}
		else
			while (++i < HEIGHT)
				data->img.buffer[column + (i * (data->img.width))] =
ground_dark(data->sol.buffer[column + ((i - (HEIGHT / 2)) * data->sol.width)],
						(HEIGHT - i) / (data->mod.nbr[DARK] == 1 ? 2 : 1) * data->calc.lum);
	else
		while (++i < HEIGHT)
			data->img.buffer[column + (i * (data->img.width))] =
						data->parse.f_color;
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
	data->calc.lum = (24. / HEIGHT * (data->mod.nbr[DARK] == 1 ? 3.8 : 1));
}

void	crt_column(t_data *data, int column)
{
	int		i;
	t_img 	rend;

	rend = get_texture(data);
	init_calc(data, rend);
	crt_sky(data, column);
	i = data->ray.start - 1;
	if (data->ray.side == 1)
		while (++i < data->ray.end)
			data->img.buffer[column + (i * (data->img.width))] =
	ground_dark(rend.buffer[(int)(data->calc.calcx + (int)((int)((i -
data->ray.truestart) * data->calc.ratio) * rend.width))], data->ray.walldist *
		20 * (data->mod.nbr[DARK] == 1 ? 1.4 : 1) * data->calc.lum);
	else
		while (++i < data->ray.end)
			data->img.buffer[column + (i * (data->img.width))] =
	ground_dark(rend.buffer[(int)(data->calc.calcy + (int)((int)((i -
data->ray.truestart) * data->calc.ratio) * rend.width))], data->ray.walldist *
		20 * (data->mod.nbr[DARK] == 1 ? 1.4 : 1) * data->calc.lum);
	crt_ground(data, column);
}

t_img	resize_image(t_data *data, t_img *src, int width, int height) 
{
	t_img	dst;
	double	size_x; 
	double	size_y; 
	int		x;
	int		y;

	size_x = (src->width / (double)width);
	size_y = (src->height / (double)height);
	dst.ptr = mlx_new_image(data->mlx.ptr, width, height);
	src->buffer = (int*)mlx_get_data_addr(src->ptr, &src->bpp, &src->size,
			&src->endian);
	dst.buffer = (int*)mlx_get_data_addr(dst.ptr, &(dst.bpp), &(dst.size),
			&(dst.endian));
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			dst.buffer[x + (y * dst.size / 4)] =
				src->buffer[(int)(((int)(x * size_x) + ((int)(y * size_y) *
								(src->size / 4))))];
		}
	}
	dst.height = height;
	dst.width = width;
	return (dst);
}
