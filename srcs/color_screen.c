/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:19:05 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 07:25:51 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_screen(t_data *data, long color)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->w)
	{
		y = -1;
		while (++y < data->h)
			data->img.buffer[x + (y * data->img.width)] = color;
	}
}

void	you_died(t_data *data)
{
	int		i;
	int		color;

	i = -1;
	while (++i < data->h * data->w)
	{
		if (i > data->h / 4 * data->w && i < data->h * 3 / 4 * data->w)
		{
			if (tolerance((color = data->you_died[
(int)data->you_died_index].buffer[i - (data->h / 4 * data->w)]), 0x99) == TRUE)
				data->img.buffer[i] = dark(data->img.buffer[i],
						(6000000.0 - data->anim) / 6000000.0);
			else if (i > data->h / 4 * data->w && i < data->h * 3 / 4 * data->w)
				data->img.buffer[i] = dark(color, (data->anim % 2) == 0 &&
			data->anim < 2000000.0 ? (2000000.0 - data->anim / 2000000.0) :
						(data->anim) / 6000000.0);
		}
		else
			data->img.buffer[i] = dark(data->img.buffer[i],
					(6000000.0 - data->anim) / 6000000.0);
	}
}

void	print_life(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->w)
	{
		y = -1;
		while (++y < data->h)
			if (x > data->life.debut_x + 7 && x < data->life.debut_x +
					data->life.max_life - data->life.hurt - 7 &&
	y > data->life.debut_y + 7 && y < data->life.debut_y + data->life.fin_y - 7)
				data->img.buffer[x + (y * data->img.width)] = 0xFF0000;
			else if (x > data->life.debut_x && x < data->life.debut_x +
	data->life.max_life && y > data->life.debut_y && y < data->life.debut_y +
								data->life.fin_y)
				data->img.buffer[x + (y * data->img.width)] = 0x330000;
	}
}

void	print_sword(t_data *data, int index)
{
	int		x;
	int		y;
	int		color;

	x = -1;
	while (++x < data->w)
	{
		y = -1;
		while (++y < data->h)
			if (x > data->w / 2)
			{
				color = data->sword[index].buffer[
					x - data->w / 2 + (y * data->sword[index].width)];
				if ((color & 0xDC6400) != 0)
					data->img.buffer[x + (y * data->img.width)] = color;
			}
	}
}

void	print_screamer(t_data *data, int index)
{
	int		x;
	int		y;
	int		color;

	x = -1;
	while (++x < data->w)
	{
		y = -1;
		while (++y < data->h)
		{
			color = data->screamer[index].buffer[
			x + (y * data->screamer[index].width)];
			data->img.buffer[x + (y * data->img.width)] = color;
		}
	}
}
