/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/05 21:09:20 by gaefourn         ###   ########.fr       */
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
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFFFF;
	i--;
	while (++i < data->ray.end)
		data->img.buffer[column + (i * (data->img.size / 4))] = color;
	i--;
	while (++i < HEIGHT)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xA0AAAAAA;
}
