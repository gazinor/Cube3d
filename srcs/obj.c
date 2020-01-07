/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:23:05 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/07 06:06:19 by glaurent         ###   ########.fr       */
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
		i = (HEIGHT / 2) - ((HEIGHT / obj->sac.ray.walldist) / 2);
		true_start = i;
		i = i < 0 ? 0 : i - 1;
		j = (HEIGHT / 2) + ((HEIGHT / obj->sac.ray.walldist) / 2);
		true_end = j;
		j = j > HEIGHT ? HEIGHT : j;
		while (++i < j)
		{
			if (obj->sac.ray.side == 1)
			{
				color = dark(rend.buffer[(int)(((obj->sac.ray.walldist * obj->sac.ray.dirx +
				data->perso.pos.x - (int)(obj->sac.ray.walldist * obj->sac.ray.dirx +
			data->perso.pos.x)) * rend.height) + (int)((int)((i - true_start) *
				(rend.height / (double)(true_end - true_start))) * (rend.size /
									sizeof(int))))], obj->sac.ray.walldist, data);
			}
			else
			{
				color = dark(rend.buffer[(int)(((obj->sac.ray.walldist * obj->sac.ray.diry +
				data->perso.pos.y - (int)(obj->sac.ray.walldist * obj->sac.ray.diry +
			data->perso.pos.y)) * rend.height) + (int)((int)((i - true_start) *
				(rend.height / (double)(true_end - true_start))) * (rend.size /
									sizeof(int))))], obj->sac.ray.walldist, data);
			}
			if (color)
			{
				data->img.buffer[obj->sac.column + (i * (data->img.size / sizeof(int)))] = color;
				if (data->mod.nbr[MIRROR] == 1 && (j - i + true_end) < HEIGHT)
					data->img.buffer[obj->sac.column + ((j - i + true_end) *
							(data->img.size / sizeof(int)))] = ground_dark(color, 5);
			}
		}
		obj = obj->next;
	}
}

void	sort_list(t_sprite **obj)
{
	t_sac tmp;
	t_sprite *head;

	head = *obj;
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

void	print_obj(t_data *data, t_sprite *obj)
{
	int	stripe;
	int	y;

	sort_list(&obj);
	while (obj)
	{
		double spriteX = obj->sac.ray.mapx - data->perso.pos.x + 0.5;
		double spriteY = obj->sac.ray.mapy - data->perso.pos.y + 0.5;
		double invDet = 1.0 / (data->perso.planx * data->perso.dir.y -
				data->perso.dir.x * data->perso.plany);
		double transformX = invDet * (data->perso.dir.y * spriteX -
				data->perso.dir.x * spriteY);
		double transformY = invDet * (-data->perso.plany * spriteX +
				data->perso.planx * spriteY);
		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		int spriteHeight = ABS((int)(HEIGHT / transformY));
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		int spriteWidth = ABS((int)(HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX - 1;
		while (++stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX))
					* data->sprite.width / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < WIDTH
					&& transformY < data->ZBuffer[stripe])
			{
				y = drawStartY - 1;
				while (++y < drawEndY)
				{
					int d = y * 256 - HEIGHT * 128 + spriteHeight * 128;
					int texY = ((d * data->sprite.height) / spriteHeight) / 256;
					int color = dark(data->sprite.buffer[data->sprite.width *
							texY + texX], obj->sac.ray.walldist, data);
					if((color & 0x00FFFFFF) != 0)
					{
						data->img.buffer[stripe + (y *
								(data->img.size / sizeof(int)))] = color;
						if (data->mod.nbr[MIRROR] == 1 && (drawEndY - y + drawEndY) < HEIGHT)
							data->img.buffer[stripe + ((drawEndY - y + drawEndY) *
(data->img.size / sizeof(int)))] = ground_dark(color, 5);
					}
				}
			}
		}
		obj = obj->next;
	}
}

void	*create_door(t_data *data, t_sprite **obj, int column)
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
	(*obj)->next = NULL;
	return (obj);
}

void	*create_obj(t_data *data, t_sprite **obj, int column)
{
	while (*obj)
	{
		if ((int)((*obj)->sac.ray.mapx) == (int)(data->ray.mapx) &&
				(int)(data->ray.mapy) == (int)((*obj)->sac.ray.mapy))
			return (obj);
		obj = &((*obj)->next);
	}
	if (!(*obj = malloc(sizeof(t_sprite))))
		return (NULL);
	++data->numSprites;
	(*obj)->sac.ray = data->ray;
	(*obj)->sac.column = column;
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
