/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/06 06:11:24 by gaefourn         ###   ########.fr       */
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
			return (0xFF0000);
		if (data->ray.stepy == 1)
			return (0x0000FF);
	}
	if (data->ray.stepx == -1)
		return (0xFFFFFF);
	return (0xEFD807);
}

void	crt_column(t_data *data, int column)
{
	int		i;
	long	color;

	i = -1;
	color = get_texture(data);
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFF000000;
	i--;
	while (++i < data->ray.end)
		data->img.buffer[column + (i * (data->img.size / 4))] = color;
	i--;
	while (++i < HEIGHT)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xAA000000;
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
