/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 09:23:05 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 06:09:43 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_norme_obj		set_obj_values(t_data *data, t_sprite *obj)
{
	t_norme_obj		f;

	f.spritex = obj->sac.ray.mapx - data->perso.pos.x + 0.5;
	f.spritey = obj->sac.ray.mapy - data->perso.pos.y + 0.5;
	f.invdet = 1.0 / (data->perso.planx * data->perso.dir.y -
	data->perso.dir.x * data->perso.plany);
	f.transformx = f.invdet * (data->perso.dir.y * f.spritex -
	data->perso.dir.x * f.spritey);
	f.transformy = f.invdet * (-data->perso.plany * f.spritex +
			data->perso.planx * f.spritey);
	f.spritescreenx = (int)(data->w / 2 * (1 + f.transformx / f.transformy));
	f.spriteheight = my_abs((int)(data->h / f.transformy));
	f.drawstarty = -f.spriteheight / 2 + data->h / 2;
	f.drawstarty < 0 ? f.drawstarty = 0 : 0;
	f.drawendy = f.spriteheight / 2 + data->h / 2;
	f.drawendy >= data->h ? f.drawendy = data->h - 1 : 0;
	f.spritewidth = my_abs((int)(data->h / (f.transformy)));
	f.drawstartx = -f.spritewidth / 2 + f.spritescreenx;
	f.drawstartx < 0 ? f.drawstartx = 0 : 0;
	f.drawendx = f.spritewidth / 2 + f.spritescreenx;
	f.drawendx >= data->w ? f.drawendx = data->w - 1 : 0;
	f.stripe = f.drawstartx - 1;
	f.luminosity = (obj->sac.ray.walldist * 600 /
			data->h * (data->mod.nbr[DARK] == 1 ? 4. : 1));
	return (f);
}

void			intern_obj(t_data *data, t_norme_obj f, t_sprite *obj)
{
	f.d = f.y * 256 - data->h * 128 + f.spriteheight * 128;
	f.texy = f.d * data->sprite.height / f.spriteheight / 256;
	if (f.spritewidth * f.texy + f.texx > 0)
	{
		f.color = ground_dark(obj->sac.img.buffer[data->sprite.width *
				f.texy + f.texx], f.luminosity);
		if ((f.color & 0x00ffffff) != 0)
		{
			data->img.buffer[f.stripe + ((f.y + obj->sac.down) *
					(data->img.width))] = f.color;
			if (data->mod.nbr[MIRROR] == 1 && (f.drawendy - f.y
						+ f.drawendy) < data->h)
				data->img.buffer[f.stripe + ((f.drawendy - f.y + f.drawendy) *
						(data->img.width))] = ground_dark(f.color, 5);
		}
	}
}

void			print_obj(t_data *data, t_sprite *obj)
{
	t_norme_obj		f;

	while (obj)
	{
		f = set_obj_values(data, obj);
		while (++f.stripe < f.drawendx)
		{
			f.texx = (int)(256 * (f.stripe - (-f.spritewidth / 2 +
			f.spritescreenx)) * data->sprite.width / f.spritewidth) / 256;
			if (f.transformy > 0 && f.stripe > 0 && f.stripe < data->w
					&& f.transformy < data->zbuffer[f.stripe])
			{
				f.y = f.drawstarty - 1;
				while (++f.y + obj->sac.down < data->h && f.y < f.drawendy)
					intern_obj(data, f, obj);
			}
		}
		obj = obj->next;
	}
}

void			*create_obj(t_data *data, t_sprite **obj, t_img img, int down)
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
	(*obj)->sac.ray = data->ray;
	(*obj)->sac.img = img;
	(*obj)->sac.down = down;
	(*obj)->next = NULL;
	return (obj);
}

void			free_obj(t_sprite *obj)
{
	t_sprite	*tmp;

	while (obj)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
	obj = NULL;
}
