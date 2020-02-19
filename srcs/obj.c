/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:23:05 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/19 06:09:16 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

void	print_door(t_data *data, t_sprite *obj, t_img rend)
{
	int		i;
	int		j;
	int		true_start;
	int		true_end;
	int		color;
	double  calc1;
	double  calc2;
	double  ratio;
	double  luminosity;

	while (obj)
	{
		i = (HEIGHT / 2) - ((HEIGHT / obj->sac.ray.walldist) / 2);
		true_start = i;
		i = i < 0 ? 0 : i - 1;
		j = (HEIGHT / 2) + ((HEIGHT / obj->sac.ray.walldist) / 2);
		true_end = j;
		j = j > HEIGHT ? HEIGHT : j;
		calc1 = ((obj->sac.ray.walldist * obj->sac.ray.dirx + data->perso.pos.x
					- (int)(obj->sac.ray.walldist * obj->sac.ray.dirx +
						data->perso.pos.x)) * rend.height);
		calc2 = ((obj->sac.ray.walldist * obj->sac.ray.diry + data->perso.pos.y
					- (int)(obj->sac.ray.walldist * obj->sac.ray.diry +
						data->perso.pos.y)) * rend.height);
		ratio = (rend.height / (double)(true_end - true_start));
		luminosity = obj->sac.ray.walldist * 600 / HEIGHT * (data->mod.nbr[DARK] == 1 ? 4. : 1);
		while (++i < j)
		{
			if (obj->sac.ray.side == 1)
				color = ground_dark(rend.buffer[(int)(calc1 + (int)((int)((i -
										true_start) * ratio) * (rend.width)))], luminosity);
			else
				color = ground_dark(rend.buffer[(int)(calc2 + (int)((int)((i -
										true_start) * ratio) * (rend.width)))], luminosity);
			if (color)
			{
				data->img.buffer[obj->sac.column + (i * (data->img.width))] = color;
				if (data->mod.nbr[MIRROR] == 1 && (j - i + true_end) < HEIGHT)
					data->img.buffer[obj->sac.column + ((j - i + true_end) *
							(data->img.width))] = ground_dark(color, 5);
			}
			else if (obj->sac.trap == 1)
				data->img.buffer[obj->sac.column + (i * (data->img.width))] = 0x0;
		}
		obj = obj->next;
	}
}

void	sort_list(t_sprite **obj)
{
	t_sac tmp;
	t_sprite *head;

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
		int spriteHeight = my_abs((int)(HEIGHT / transformY));
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		int spriteWidth = my_abs((int)(HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX - 1;
		double luminosity = (obj->sac.ray.walldist * 600 / HEIGHT * (data->mod.nbr[DARK] == 1 ? 4. : 1));
		while (++stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX))
					* obj->sac.img.width / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < WIDTH
					&& transformY < data->ZBuffer[stripe])
			{
				y = drawStartY - 1;
				while (++y + obj->sac.down < HEIGHT && y < drawEndY)
				{
					int d = y * 256 - HEIGHT * 128 + spriteHeight * 128;
					int texY = ((d * obj->sac.img.height) / spriteHeight) / 256;
					if (spriteWidth * (texY) + texX > 0)
					{
						int color = ground_dark(obj->sac.img.buffer[obj->sac.img.width *
								(texY) + texX], luminosity);
						if((color & 0x00FFFFFF) != 0)
						{
							data->img.buffer[stripe + ((y + obj->sac.down) *
									(data->img.width))] = color;
							if (data->mod.nbr[MIRROR] == 1 && (drawEndY - y + drawEndY) < HEIGHT)
								data->img.buffer[stripe + ((drawEndY - y + drawEndY) *
										(data->img.width))] = ground_dark(color, 5);
						}
					}
				}
			}
		}
		obj = obj->next;
	}
}

void	print_portal(t_data *data, t_portal *portal, int index)
{
	int	stripe;
	int	y;

	while (portal)
	{
		double spriteX = portal->ray.mapx - data->perso.pos.x + 0.5;
		double spriteY = portal->ray.mapy - data->perso.pos.y + 0.5;
		double invDet = 1.0 / (data->perso.planx * data->perso.dir.y -
				data->perso.dir.x * data->perso.plany);
		double transformX = invDet * (data->perso.dir.y * spriteX -
				data->perso.dir.x * spriteY);
		double transformY = invDet * (-data->perso.plany * spriteX +
				data->perso.planx * spriteY);
		int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		int spriteHeight = my_abs((int)(HEIGHT / transformY));
		int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if(drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		int spriteWidth = my_abs((int)(HEIGHT / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX - 1;
		double luminosity = (portal->ray.walldist * 600 / HEIGHT * (data->mod.nbr[DARK] == 1 ? 4. : 1));
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
					if (spriteWidth * texY + texX > 0)
					{
						int color = ground_dark(data->portal[index].buffer[data->sprite.width *
							texY + texX], luminosity);
						if((color & 0x00FFFFFF) != 0)
						{
							data->img.buffer[stripe + (y *
									(data->img.width))] = color;
							if (data->mod.nbr[MIRROR] == 1 && (drawEndY - y + drawEndY) < HEIGHT)
								data->img.buffer[stripe + ((drawEndY - y + drawEndY) *
									(data->img.width))] = ground_dark(color, 5);
						}
					}
				}
			}
		}
		portal = portal->next;
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
	if (data->map[(int)data->ray.mapx][(int)data->ray.mapy] == '5')
		(*obj)->sac.trap = 1;
	else
		(*obj)->sac.trap = 0;
	(*obj)->next = NULL;
	return (obj);
}

t_pos	set_dir_portal(char c)
{
	t_pos	dir;

	dir.y = 0;
	dir.x = -1;
	if (c == 'P' || c == 'T')
	{
		dir.y = (c == 'P') ? 0 : 0;
		dir.x = (c == 'P') ? 1 : -1;
	}
	else if (c == 'O' || c == 'A')
	{
		dir.y = (c == 'O') ? -1 : 1;
		dir.x = (c == 'O') ? 0 : 0;
	}
	else if (c == 'R' || c == 'L')
	{
		dir.y = (c == 'R') ? 1 : -1;
		dir.x = (c == 'R') ? 0 : 0;
	}
	return (dir);
}

void    *create_portal(t_data *data, t_portal **portal_lst)
{
	while (*portal_lst)
	{
		if ((*portal_lst)->ray.mapx == data->ray.mapx &&
				(*portal_lst)->ray.mapy == data->ray.mapy)
			return (portal_lst);
		portal_lst = &((*portal_lst)->next);
	}
	if (!(*portal_lst = malloc(sizeof(t_portal))))
		return (NULL);
	(*portal_lst)->ray = data->ray;
	(*portal_lst)->next = NULL;
	return (portal_lst);
}

void	*create_obj(t_data *data, t_sprite **obj, t_img img, int down)
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
	(*obj)->sac.img = img;
	(*obj)->sac.down = down;
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

void	free_portal(t_portal *obj)
{
	t_portal	*tmp;

	while (obj)
	{
		tmp =  obj->next;
		free(obj);
		obj = tmp;
	}
	obj = NULL;
}
