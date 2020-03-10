/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:39:57 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/08 23:45:04 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_norme_door	set_door_vars(t_data *data, t_sprite *obj, t_img rend)
{
	t_norme_door	f;

	f.i = (data->h / 2) - ((data->h / obj->sac.ray.walldist) / 2);
	f.true_start = f.i;
	f.i = f.i < 0 ? 0 : f.i - 1;
	f.j = (data->h / 2) + ((data->h / obj->sac.ray.walldist) / 2);
	f.t_e = f.j;
	f.j = f.j > data->h ? data->h : f.j;
	f.calc1 = ((obj->sac.ray.walldist * obj->sac.ray.dirx + data->perso.pos.x
				- (int)(obj->sac.ray.walldist * obj->sac.ray.dirx +
					data->perso.pos.x)) * rend.height);
	f.calc2 = ((obj->sac.ray.walldist * obj->sac.ray.diry + data->perso.pos.y
				- (int)(obj->sac.ray.walldist * obj->sac.ray.diry +
					data->perso.pos.y)) * rend.height);
	f.ratio = (rend.height / (double)(f.t_e - f.true_start));
	f.luminosity = obj->sac.ray.walldist * 600 / data->h *
		(data->mod.nbr[DARK] == 1 ? 4. : 1);
	return (f);
}

void			print_door(t_data *data, t_sprite *obj, t_img rend)
{
	t_norme_door	f;

	while (obj)
	{
		f = set_door_vars(data, obj, rend);
		while (++f.i < f.j)
		{
			f.color = ground_dark(rend.buffer[(int)(((obj->sac.ray.side == 1) ?
			f.calc1 : f.calc2) + (int)((int)((f.i - f.true_start) * f.ratio) *
				(rend.width)))], f.luminosity);
			if (f.color)
			{
				data->img.buffer[obj->sac.column +
					(f.i * (data->img.width))] = f.color;
				if (data->mod.nbr[MIRROR] == 1 && (f.j - f.i + f.t_e) < data->h)
					data->img.buffer[obj->sac.column + ((f.j - f.i + f.t_e) *
							(data->img.width))] = ground_dark(f.color, 5);
			}
			else if (obj->sac.trap == 1)
				data->img.buffer[obj->sac.column +
					(f.i * (data->img.width))] = 0x0;
		}
		obj = obj->next;
	}
}

void			*create_door(t_data *data, t_sprite **obj, int column)
{
	while (*obj)
	{
		if ((*obj)->sac.column == column && data->event.door == FALSE)
			return (obj);
		obj = &((*obj)->next);
	}
	if (!(*obj = malloc(sizeof(t_sprite))))
		return (NULL);
	(*obj)->sac.ray = data->ray;
	(*obj)->sac.column = column;
	if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '5')
		(*obj)->sac.trap = 1;
	else
		(*obj)->sac.trap = 0;
	(*obj)->next = NULL;
	return (obj);
}

void			sort_list(t_sprite **obj)
{
	t_sac		tmp;
	t_sprite	*head;

	head = *obj;
	if (!*obj)
		return ;
	while (*obj && (*obj)->next)
	{
		if ((*obj)->sac.ray.walldist < (*obj)->next->sac.ray.walldist)
		{
			tmp = (*obj)->sac;
			(*obj)->sac = (*obj)->next->sac;
			(*obj)->next->sac = tmp;
			obj = &head;
		}
		else
			obj = &(*obj)->next;
	}
}

void			free_portal(t_portal *obj)
{
	t_portal	*tmp;

	if (obj)
	{
		while (obj)
		{
			tmp = obj->next;
			free(obj);
			obj = tmp;
		}
		obj = NULL;
	}
}
