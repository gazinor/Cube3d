/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:23:05 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/17 11:29:49 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

void	print_door(t_data *data, t_sprite *obj)
{
	int		i;
	int		j;
	int		true_start;
	int		true_end;
	t_img	rend;
	int		color;

	rend = data->event.door == FALSE ? data->cdoor : data->odoor;
	while (obj)
	{
		i = (HEIGHT / 2) - ((HEIGHT / obj->ray.walldist) / 2);
		true_start = i;
		i = i < 0 ? 0 : i - 1;
		j = (HEIGHT / 2) + ((HEIGHT / obj->ray.walldist) / 2);
		true_end = j;
		j = j > HEIGHT ? HEIGHT : j;
		while (++i < j)
		{
			if (obj->ray.side == 1)
			{
				color = dark(rend.buffer[(int)(((obj->ray.walldist * obj->ray.dirx +
	data->perso.pos.x - (int)(obj->ray.walldist * obj->ray.dirx +
	data->perso.pos.x)) * rend.height) + (int)((int)((i - true_start) *
	(rend.height / (double)(true_end - true_start))) * (rend.size /
sizeof(int))))], obj->ray.walldist, data);
				
			}
			else
			{
				color = dark(rend.buffer[(int)(((obj->ray.walldist * obj->ray.diry +
	data->perso.pos.y - (int)(obj->ray.walldist * obj->ray.diry +
	data->perso.pos.y)) * rend.height) + (int)((int)((i - true_start) *
	(rend.height / (double)(true_end - true_start))) * (rend.size /
sizeof(int))))], obj->ray.walldist, data);
			}
			if (color)
			{
				data->img.buffer[obj->column + (i * (data->img.size / sizeof(int)))] = color;
    			if (data->mod.nbr[MIRROR] == 1 && (j - i + true_end) < HEIGHT)
					data->img.buffer[obj->column + ((j - i + true_end) *
(data->img.size / sizeof(int)))] = trans(color, data, j - i + true_end, HEIGHT);
			}
		}
		obj = obj->next;
	}
}

void	print_obj(t_data *data, t_sprite *obj)
{
	int		i;
	int		j;
	int		true_start;
	int		true_end;
	t_img	rend;
	int		color;
	int		tmp;

	rend = data->sprite;
	tmp = obj->column + obj->ray.heightline;
	while (obj)
	{
		while (obj->column < tmp && obj->column < WIDTH)
		{
			i = obj->ray.start;
			true_start = i;
			i = i < 0 ? -1 : i - 1;
			j = obj->ray.end;
			true_end = j;
			j = j > HEIGHT ? HEIGHT : j;
			while (++i < j)
			{
				color = dark(rend.buffer[(obj->column + obj->ray.heightline - tmp) + ((int)((int)(i - true_start) * (rend.height / (true_end - true_start) * (rend.size / sizeof(int)))))], obj->ray.walldist, data);
				if (color)
				{
					data->img.buffer[obj->column + (i * (data->img.size / sizeof(int)))] = color;
	    			if (data->mod.nbr[MIRROR] == 1 && (j - i + true_end) < HEIGHT)
						data->img.buffer[obj->column + ((j - i + true_end) *
	(data->img.size / sizeof(int)))] = trans(color, data, j - i + true_end, HEIGHT);
				}
			}
			++obj->column;
		}
		obj = obj->next;
	}
}

void	*create_door(t_data *data, t_sprite **obj, int column)
{
	while (*obj)
	{
		if ((*obj)->column == column && data->event.door == FALSE)
			return (obj);
		obj = &((*obj)->next);
	}
	if (!(*obj = malloc(sizeof(t_sprite))))
		return (NULL);
	(*obj)->ray = data->ray;
	(*obj)->column = column;
	(*obj)->next = NULL;
	return (obj);
}

void	*create_obj(t_data *data, t_sprite **obj, int column)
{
	while (*obj)
	{
		if ((int)((*obj)->ray.mapx) == (int)(data->ray.mapx) &&
				(int)(data->ray.mapy) == (int)((*obj)->ray.mapy))
			return (obj);
		obj = &((*obj)->next);
	}
	if (!(*obj = malloc(sizeof(t_sprite))))
		return (NULL);
	(*obj)->ray = data->ray;
	(*obj)->column = column;
	(*obj)->next = NULL;
	return (obj);
}

void	free_obj(t_sprite *obj)
{
	t_sprite	*tmp;

	while (obj)
	{
		tmp =  obj->next;
		free(obj);
		obj = tmp;
	}
	obj = NULL;
}
