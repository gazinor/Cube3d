/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/06 11:51:15 by glaurent         ###   ########.fr       */
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

long	get_texture(t_data *data)
{
	if (data->ray.side == 1)
	{
		if (data->ray.stepy == -1)
			return (0x00FF0000);
		if (data->ray.stepy == 1)
			return (0x000000FF);
	}
	if (data->ray.stepx == -1)
		return (0x00FFFFFF);
	return (0x00EFD807);
}

long	dark(long *color, double walldist)
{
	unsigned char	*blue;
	double			calcul;

	blue = (unsigned char *)color;
	calcul = ((walldist / 7.5) + 1);
	*blue = *blue / calcul;
	++blue;
	*blue = *blue / calcul;
	++blue;
	*blue = *blue / calcul;
	++blue;
	*blue = 0;
	return (*color);
}

long	trans(long *color, t_data *data, int i)
{
	unsigned char	*blue;
	double			calcul;
	double			calcul2;

	blue = (unsigned char *)color;
	calcul = ((data->ray.walldist / 7.5) + 1);
	calcul2 = (i * ((data->ray.end - data->ray.start) / HEIGHT) +
											(data->ray.walldist * 3.5)) * 10.5;
	*blue = *blue / calcul;
	++blue;
	*blue = *blue / calcul;
	++blue;
	*blue = *blue / calcul;
	++blue;
	if (*blue + calcul2 < 255 && i < data->ray.end +
											(data->ray.end - data->ray.start))
		*blue += calcul2;
	else
		*blue = 255;
	return (*color);
}

void	crt_column(t_data *data, int column)
{
	int		i;
	long	color;
	long 	rend;

	i = -1;
	color = get_texture(data);
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFF000000;
	i--;
	while (++i < data->ray.end)
	{
		rend = color;
		data->img.buffer[column + (i * (data->img.size / 4))] = dark(&rend, data->ray.walldist);
	}
	i--;
	while (++i < HEIGHT)
	{
		rend = color;
		//*blue = *blue / ((data->ray.walldist / 16.) + 1);
		data->img.buffer[column + (i * (data->img.size / 4))] = trans(&rend, data, i);
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
