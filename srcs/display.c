/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/06 02:20:50 by glaurent         ###   ########.fr       */
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

	if (column == HEIGHT / 2)
		printf("old  : %d , start : %d\n", data->ray.old_strt[column], data->ray.start);
	color = get_texture(data);
	i = data->ray.old_strt[column] - 1;
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFFFF;
	--i;
	while (++i < data->ray.end && i < HEIGHT)
		data->img.buffer[column + (i * (data->img.size / 4))] = color;
	--i;
	while (++i < HEIGHT && i <= data->ray.old_end[column])
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xA0AAAAAA;
	data->ray.old_strt[column] = data->ray.start;
	data->ray.old_end[column] = data->ray.end;
}
/*------------------------------------------------------*/
/* pixel actuel * taille de l'image / taille de l'ecran */
/*------------------------------------------------------*/
