/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:23:05 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/11 11:29:50 by glaurent         ###   ########.fr       */
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

	rend = data->event.door == 0 ? data->cdoor : data->odoor; 
	while (obj)
	{
		i = (HEIGHT / 2) - ((HEIGHT / obj->ray.walldist) / 2);
		true_start = i;
		i = i < 0 ? 0 : i - 1;
		j = (HEIGHT / 2) + ((HEIGHT / obj->ray.walldist) / 2);
		true_end = j;
		j = j > HEIGHT ? HEIGHT : j;
		while (++i < j)
			if (obj->ray.side == 1)
			{
				color = dark(rend.buffer[(int)(((obj->ray.walldist * obj->ray.dirx +
	data->perso.pos.x - (int)(obj->ray.walldist * obj->ray.dirx +
	data->perso.pos.x)) * rend.height) + (int)((int)((i - true_start) *
	(rend.height / (double)(true_end - true_start))) * (rend.size /
sizeof(int))))], obj->ray.walldist, data);
				if (color)
					data->img.buffer[obj->column + (i * (data->img.size / sizeof(int)))] = color;
			}
			else
			{
				color = dark(rend.buffer[(int)(((obj->ray.walldist * obj->ray.diry +
	data->perso.pos.y - (int)(obj->ray.walldist * obj->ray.diry +
	data->perso.pos.y)) * rend.height) + (int)((int)((i - true_start) *
	(rend.height / (double)(true_end - true_start))) * (rend.size /
sizeof(int))))], obj->ray.walldist, data);
				if (color)
					data->img.buffer[obj->column + (i * (data->img.size / sizeof(int)))] = color;
			}
    if (data->mod.nbr[MIRROR] == 1)
		while (++i < HEIGHT)
    	    data->img.buffer[obj->column + (i * (data->img.size / sizeof(int)))] =
trans(data->img.buffer[obj->column + ((obj->ray.end - (i - obj->ray.end)) *
(data->img.size / sizeof(int)))], data, i, 2 * obj->ray.end - obj->ray.start);
		obj = obj->next;
	}
}

void	*create_door(t_data *data, t_sprite **obj, int column)
{
	char toggle;
	
	toggle = 0;
	while (*obj)
	{
		if ((*obj)->column == column)
			toggle = 1;
		obj = &((*obj)->next);
	}
	if (!toggle)
	{
		if (!(*obj = malloc(sizeof(t_data))))
			return (NULL);
		(*obj)->ray = data->ray;
		(*obj)->column = column;
		(*obj)->next = NULL;
	}
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
