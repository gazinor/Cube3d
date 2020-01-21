/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:49 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/21 06:54:38 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, int x)
{
	data->ray.camera = (2 * x / (double)WIDTH) - 1;
	data->ray.dirx = data->perso.dir.x + data->perso.planx * data->ray.camera;
	data->ray.diry = data->perso.dir.y + data->perso.plany * data->ray.camera;
	data->ray.mapx = (int)data->perso.pos.x;
	data->ray.mapy = (int)data->perso.pos.y;
	data->ray.sidedistx = 0;
	data->ray.sidedisty = 0;
	data->ray.deltax = sqrt(1 + ((data->ray.diry * data->ray.diry) /
				(data->ray.dirx * data->ray.dirx)));
	data->ray.deltay = sqrt(1 + ((data->ray.dirx * data->ray.dirx) /
				(data->ray.diry * data->ray.diry)));
	data->ray.stepx = 0;
	data->ray.stepy = 0;
	data->ray.hit = 0;
	data->ray.side = 0;
	data->ray.walldist = 0;
	data->numSprites = 0;
}

void	init_filenames(t_data *data)
{
	data->ciel.filename = "./textures/ciel.xpm";
	data->sol.filename = "./textures/sol.xpm";
	data->ciel_etoile.filename = "./textures/ciel_etoile.xpm";
	data->ntext.filename = "./textures/ntext.xpm";
	data->stext.filename = "./textures/stext.xpm";
	data->etext.filename = "./textures/etext.xpm";
	data->wtext.filename = "./textures/wtext.xpm";
	data->cdoor.filename = "./textures/cdoor.xpm";
	data->odoor.filename = "./textures/odoor.xpm";
	data->remote.filename = "./textures/remote.xpm";
	data->sprite.filename = "./textures/sprite.xpm";
	data->i_menu.filename = "./textures/menu.xpm";
	data->play_s_contour.filename = "./textures/play_s_contour.xpm";
	data->play_uns_contour.filename = "./textures/play_uns_contour.xpm";
	data->option_s_contour.filename = "./textures/option_s_contour.xpm";
	data->option_uns_contour.filename = "./textures/option_uns_contour.xpm";
	data->quit_s_contour.filename = "./textures/quit_s_contour.xpm";
	data->quit_uns_contour.filename = "./textures/quit_uns_contour.xpm";
	data->on_button.filename = "./textures/on_button.xpm";
	data->off_button.filename = "./textures/off_button.xpm";
	data->retour_s.filename = "./textures/retour_s.xpm";
	data->retour_uns.filename = "./textures/retour_uns.xpm";
	data->mode_bonus.filename = "./textures/mode_bonus.xpm";
}

void	ft_init(t_data *data)
{
	data->perso.pos.x = 0;
	data->perso.pos.y = 0;
	data->perso.dir.x = 0;
	data->perso.dir.y = 0;
	data->perso.speed = 0.066;
	data->perso.rot = 6. / 180;
	data->perso.planx = 0;
	data->perso.plany = 0;
	data->event.forward = 0;
	data->event.backward = 0;
	data->event.left = 0;
	data->event.right = 0;
	data->event.l_arrow = 0;
	data->event.r_arrow = 0;
	data->event.door = 0;
	data->event.run = 0;
	data->event.respawn = 0;
	data->event.screenshot = 0;
	data->event.option = 0;
	data->mod.light = 5.;
	data->mod.i = 0;
	data->mod.nbr[NORMAL] = TRUE;
	data->mod.nbr[DARK] = FALSE;
	data->mod.nbr[MIRROR] = FALSE;
	data->map_mid.x = 0;
	data->map_mid.y = 0;
	ft_init_map(data);
	data->door = NULL;
	data->obj = NULL;
	data->option.status = 0;
	data->parse.width = 0;
	data->parse.height = 0;
	init_filenames(data);
}
