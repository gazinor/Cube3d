/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/20 09:44:34 by glaurent         ###   ########.fr       */
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
	if (data->map[(int)data->ray.mapx][(int)(data->ray.mapy)] == '0')
	{
		if (data->ray.side == 1)
		{
			if (data->ray.stepy == -1)
				return (data->ntext);
			if (data->ray.stepy == 1)
				return (data->stext);
		}
		if (data->ray.stepx == -1)
			return (data->etext);
	}
	return (data->wtext);
}

long	dark(int color, double walldist, t_data *data)
{
	unsigned char	*byte;
	double			calcul;

	byte = (unsigned char *)&color;
	calcul = ((walldist / (4.5 * data->mod.light)) + 1);
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = 0;
	return ((long)color);
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

void	crt_column(t_data *data, int column)
{
	int		i;
	t_img	texture;
	t_img 	rend;
	double	calcx;
	double	calcy;
	double	ratio;
	double	luminosity;
	double	offset;

	i = -1;
	texture = get_texture(data);
	rend = texture;
	offset = (atan2(data->ray.dirx, data->ray.diry) + M_PI) * M_1_PI * .5;
	calcx = ((data->ray.walldist * data->ray.dirx + data->perso.pos.x - (int)(
	data->ray.walldist * data->ray.dirx + data->perso.pos.x)) * texture.height);
	calcy = ((data->ray.walldist * data->ray.diry + data->perso.pos.y - (int)(
	data->ray.walldist * data->ray.diry + data->perso.pos.y)) * texture.height);
	ratio = (texture.height / (double)data->ray.heightline);
	data->img.width = data->img.size / 4;
	luminosity = (0.040 * 600 / HEIGHT * (data->mod.nbr[DARK] == 1 ? 1.3 : 1));
	if (data->mod.nbr[DARK] == 1)
       while (++i < data->ray.start)
           data->img.buffer[column + (i * (data->img.width))] =
	   data->ciel_etoile.buffer[(int)((offset + i) * data->ciel_etoile.width)];
   else
       while (++i < data->ray.start)
           data->img.buffer[column + (i * (data->img.width))] =
		data->ciel.buffer[(int)((offset + i) * data->ciel.width)];
	i--;
	if (data->ray.side == 1)
		while (++i < data->ray.end)
			data->img.buffer[column + (i * (data->img.width))]
= ground_dark(rend.buffer[(int)(calcx + (int)((int)((i - data->ray.truestart) * ratio)
		* rend.width))], data->ray.walldist / 0.040 * luminosity);
	else
		while (++i < data->ray.end)
			data->img.buffer[column + (i * (data->img.width))]
= ground_dark(rend.buffer[(int)(calcy + (int)((int)((i - data->ray.truestart) * ratio)
		* rend.width))], data->ray.walldist / 0.040 * luminosity);
	i--;
	if (data->mod.nbr[MIRROR] == 1)
	{
		while (++i < HEIGHT && i < data->ray.end + data->ray.heightline)
				data->img.buffer[column + (i * (data->img.width))] =
ground_dark(data->img.buffer[column + ((data->ray.end - (i - data->ray.end)) *
(data->img.width))], 5);
		while (++i < HEIGHT)
				data->img.buffer[column + (i * (data->img.width))] =
ground_dark(data->img.buffer[column + (data->ray.end - (i - data->ray.end) -
data->ray.heightline) *	data->img.width], (HEIGHT - i) * luminosity);
	}
	else
		while (++i < HEIGHT)
			data->img.buffer[column + (i * (data->img.width))] =
ground_dark(data->sol.buffer[column + ((i - (HEIGHT / 2)) * data->sol.width)], (HEIGHT - i) * luminosity);
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
