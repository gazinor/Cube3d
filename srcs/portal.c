/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 06:42:21 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 06:44:16 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_norme_obj		set_portal_values(t_data *data, t_portal *portal)
{
	t_norme_obj		f;

	f.spritex = portal->ray.mapx - data->perso.pos.x + 0.5;
	f.spritey = portal->ray.mapy - data->perso.pos.y + 0.5;
	f.invdet = 1.0 / (data->perso.planx * data->perso.dir.y -
	data->perso.dir.x * data->perso.plany);
	f.transformx = f.invdet * (data->perso.dir.y * f.spritex -
	data->perso.dir.x * f.spritey);
	f.transformy = f.invdet * (-data->perso.plany * f.spritex +
	data->perso.planx * f.spritey);
	f.spritescreenx = (int)(WIDTH / 2 * (1 + f.transformx / f.transformy));
	f.spriteheight = my_abs((int)(HEIGHT / f.transformy));
	f.drawstarty = -f.spriteheight / 2 + HEIGHT / 2;
	f.drawstarty < 0 ? f.drawstarty = 0 : 0;
	f.drawendy = f.spriteheight / 2 + HEIGHT / 2;
	f.drawendy >= HEIGHT ? f.drawendy = HEIGHT - 1 : 0;
	f.spritewidth = my_abs((int)(HEIGHT / (f.transformy)));
	f.drawstartx = -f.spritewidth / 2 + f.spritescreenx;
	f.drawstartx < 0 ? f.drawstartx = 0 : 0;
	f.drawendx = f.spritewidth / 2 + f.spritescreenx;
	f.drawendx >= WIDTH ? f.drawendx = WIDTH - 1 : 0;
	f.stripe = f.drawstartx - 1;
	f.luminosity = (portal->ray.walldist * 600 /
			HEIGHT * (data->mod.nbr[DARK] == 1 ? 4. : 1));
	return (f);
}

void			intern_portal(t_data *data, int index, t_norme_obj f)
{
	f.d = f.y * 256 - HEIGHT * 128 + f.spriteheight * 128;
	f.texy = f.d * data->sprite.height / f.spriteheight / 256;
	if (f.spritewidth * f.texy + f.texx > 0)
	{
		f.color = ground_dark(data->portal[index].buffer[data->sprite.width *
				f.texy + f.texx], f.luminosity);
		if ((f.color & 0x00ffffff) != 0)
		{
			data->img.buffer[f.stripe + (f.y * (data->img.width))] = f.color;
			if (data->mod.nbr[MIRROR] == 1 && (f.drawendy - f.y
						+ f.drawendy) < HEIGHT)
				data->img.buffer[f.stripe + ((f.drawendy - f.y + f.drawendy) *
						(data->img.width))] = ground_dark(f.color, 5);
		}
	}
}

void			print_portal(t_data *data, t_portal *portal, int index)
{
	t_norme_obj		f;

	while (portal)
	{
		f = set_portal_values(data, portal);
		while (++f.stripe < f.drawendx)
		{
			f.texx = (int)(256 * (f.stripe - (-f.spritewidth / 2 +
			f.spritescreenx)) * data->sprite.width / f.spritewidth) / 256;
			if (f.transformy > 0 && f.stripe > 0 && f.stripe < WIDTH
					&& f.transformy < data->zbuffer[f.stripe])
			{
				f.y = f.drawstarty - 1;
				while (++f.y < f.drawendy)
					intern_portal(data, index, f);
			}
		}
		portal = portal->next;
	}
}

t_pos			set_dir_portal(char c)
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

void			*create_portal(t_data *data, t_portal **portal_lst)
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
