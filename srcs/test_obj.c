/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:23:05 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/13 07:40:35 by glaurent         ###   ########.fr       */
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
			(data->img.size / sizeof(int)))] = trans(color, data,
			 j - i + true_end, HEIGHT);
			}
		}
		obj = obj->next;
	}
}

t_sprite	**check_door(t_data *data)
{
	int		i;

	i = -1;
	while (data->door[++i])
	{
		if (data->door[i].pos.x == data->mapx &&
				data->door[i].pos.y == data->mapy)
			return (data->door[i]);
	}
	if (!(*obj[i] = malloc(sizeof(*obj))))
		return (NULL);
	return (*obj);
}

void	*create_door(t_data *data int column)
{
	t_sprite	*door;
	char		toggle;
	
	toggle = 0;
	door = check_door(data);
	while (door)
	{
		if ((*door)->column == column && data->event.door == FALSE)
			toggle = 1;
		door = &((*door)->next);
	}
	if (!toggle)
	{
		if (!(*door = malloc(sizeof(t_sprite))
			return (NULL);
		(*door)->ray = data->ray;
		(*door)->column = column;
		(*door)->pos.x = data->mapx;
		(*door)->pos.y = data->mapy;
		(*door)->next = NULL;
	}
	return (*obj);
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
