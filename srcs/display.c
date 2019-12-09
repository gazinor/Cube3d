/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/09 02:18:08 by glaurent         ###   ########.fr       */
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

int		*get_texture(t_data *data)
{
	if (data->ray.side == 1)
	{
		if (data->ray.stepy == -1)
			return (data->ntext.buffer);
		if (data->ray.stepy == 1)
			return (data->stext.buffer);
	}
	if (data->ray.stepx == -1)
		return (data->etext.buffer);
	return (data->wtext.buffer);
}

long	dark(int color, double walldist)
{
	unsigned char	*byte;
	double			calcul;

	byte = (unsigned char *)&color;
	calcul = ((walldist / 10.5) + 1);
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = 0;
	return ((long)color);
}

long	trans(int color, t_data *data, int i)
{
	unsigned char	*byte;
	double			calcul;
	double			calcul2;

	byte = (unsigned char *)&color;
	calcul = ((data->ray.walldist / 10.5) + 1);
	calcul2 = (i * ((data->ray.end - data->ray.start) / HEIGHT) +
											(data->ray.walldist)) * 16.5;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	*byte = *byte / calcul;
	++byte;
	if (*byte + calcul2 < 255 && i < 2 * data->ray.end - data->ray.start)
		*byte += calcul2;
	else
		*byte = 255;
	return ((long)color);
}

void	crt_column(t_data *data, int column)
{
	int		i;
	int		*texture;
	int 	*rend;

	i = -1;
	texture = get_texture(data);
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFF000000;
	i--;
	while (++i < data->ray.end)
	{
		rend = texture;
		if (data->ray.side == 1)
			data->img.buffer[column + (i * (data->img.size / sizeof(int)))]
= dark(rend[(int)(((data->ray.walldist * data->ray.dirx + data->perso.pos.x -
(int)(data->ray.walldist * data->ray.dirx + data->perso.pos.x)) * 750) +
(int)((int)((i - data->ray.truestart) * (750 / (double)data->ray.heightline)) * (data->ntext.size / sizeof(int))))], data->ray.walldist);
		else
			data->img.buffer[column + (i * (data->img.size / sizeof(int)))]
= dark(rend[(int)(((data->ray.walldist * data->ray.diry + data->perso.pos.y -
(int)(data->ray.walldist * data->ray.diry + data->perso.pos.y)) * 750) +
(int)((int)((i - data->ray.truestart) * (750 / (double)data->ray.heightline)) * (data->ntext.size / sizeof(int))))], data->ray.walldist);
	}
	i--;
	while (++i < HEIGHT)
	{
		data->img.buffer[column + (i * (data->img.size / sizeof(int)))] =
trans(data->img.buffer[column + ((data->ray.end - (i - data->ray.end)) * (data->img.size / sizeof(int)))], data, i);
	}
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
	return (dst);
}

/*------------------------------------------------------*/
/* pixel actuel * taille de l'image / taille de l'ecran */
/*------------------------------------------------------*/
