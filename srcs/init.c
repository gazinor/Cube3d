/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:49 by gaefourn          #+#    #+#             */
/*   Updated: 2020/02/12 08:48:28 by glaurent         ###   ########.fr       */
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
	int		i;

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
	data->spikes.filename = "./textures/spikes.xpm";
	data->plafond.filename = "./textures/plafond.xpm";
	i = -1;
	while (++i < NB_PORTAL_IMG)
		data->portal[i].filename = g_portal[i];
	i = -1;
	while (++i < NB_SWORD_IMG)
		data->sword[i].filename = g_sword[i];
	i = -1;
	while (++i < NB_YOU_DIED_IMG)
		data->you_died[i].filename = g_you_died[i];
	i = -1;
	while (++i < NB_PLAYER2_IMG)
		data->player2[i].filename = g_player2[i];
	i = -1;
	while (++i < NB_DOOR_IMG)
		data->gif_door[i].filename = g_door[i];
	i = -1;
	while (++i < NB_SCREAMER_IMG)
		data->screamer[i].filename = g_screamer[i];
	i = -1;
	while (++i < NB_MONSTER_IMG)
		data->monster[i].filename = g_monster[i];
}

void	init_img(t_data *data)
{
	int		i;

	data->ciel.ptr = NULL;
	data->ciel_etoile.ptr = NULL;
	data->sol.ptr = NULL;
	data->ntext.ptr = NULL;
	data->stext.ptr = NULL;
	data->etext.ptr = NULL;
	data->wtext.ptr = NULL;
	data->odoor.ptr = NULL;
	data->cdoor.ptr = NULL;
	data->remote.ptr = NULL;
	data->i_menu.ptr = NULL;
	data->play_s_contour.ptr = NULL;
	data->play_uns_contour.ptr = NULL;
	data->option_s_contour.ptr = NULL;
	data->option_uns_contour.ptr = NULL;
	data->quit_s_contour.ptr = NULL;
	data->quit_uns_contour.ptr = NULL;
	data->on_button.ptr = NULL;
	data->off_button.ptr = NULL;
	data->mode_bonus.ptr = NULL;
	data->retour_s.ptr = NULL;
	data->retour_uns.ptr = NULL;
	data->sprite.ptr = NULL;
	i = -1;
	while (++i < NB_PORTAL_IMG)
		data->portal[i].ptr = NULL;
	i = -1;
	while (++i < NB_SWORD_IMG)
		data->sword[i].ptr = NULL;
	i = -1;
	while (++i < NB_PLAYER2_IMG)
		data->player2[i].ptr = NULL;
	i = -1;
	while (++i < NB_YOU_DIED_IMG)
		data->you_died[i].ptr = NULL;
	i = -1;
	while (++i < NB_DOOR_IMG)
		data->gif_door[i].ptr = NULL;
	i = -1;
	while (++i < NB_SCREAMER_IMG)
		data->screamer[i].ptr = NULL;
	i = -1;
	while (++i < NB_MONSTER_IMG)
		data->monster[i].ptr = NULL;
}

void	ft_init_player(t_data *data)
{
	data->perso.speed = 0.066;
	data->perso.rot = 6. / 180;
	data->event.forward = 0;
	data->event.backward = 0;
	data->event.left = 0;
	data->event.right = 0;
	data->event.l_arrow = 0;
	data->event.r_arrow = 0;
	data->event.door = 0;
	data->event.remote = 0;
	data->event.run = 0;
	data->event.respawn = 0;
	data->event.screenshot = 0;
	data->event.option = 0;
	data->event.hit = 0;
	data->mod.light = 5.;
	data->mod.i = 0;
	data->mod.nbr[NORMAL] = TRUE;
	data->mod.nbr[DARK] = FALSE;
	data->mod.nbr[MIRROR] = FALSE;
	data->life.debut_x = WIDTH * 5 / 8;
	data->life.debut_y = HEIGHT / 16;
	data->life.fin_y = HEIGHT / 32;
	data->life.max_life = WIDTH / 4;
	data->life.hurt = 0;
	data->life.hit = 10 * data->life.max_life / 100.;
	data->life.blood = 0;
	data->life.alive = TRUE;
	data->portal_index = 0;
	data->sword_index = NB_SWORD_IMG;
	data->you_died_index = 0;
	data->player2_index = 0;
	data->door_index = 0;
	data->screamer_index = 0;
	data->time.tv_usec = 0;
	data->time.tv_sec = 0;
}

void	ft_init(t_data *data)
{
	int		i;

	ft_init_player(data);
	data->perso.pos.x = 0;
	data->perso.pos.y = 0;
	data->perso.dir.x = 0;
	data->perso.dir.y = 0;
	data->map = NULL;
	data->perso.planx = 0;
	data->perso.plany = 0;
	data->map_mid.x = 0;
	data->map_mid.y = 0;
	ft_init_map(data);
	data->door = NULL;
	data->obj = NULL;
	data->player = NULL;
	data->monster_lst = NULL;
	data->portal_lst = NULL;
	data->option.status = 0;
	data->w = 0;
	data->h = 0;
	data->parse.nb_line = 0;
	data->parse.sizeline = 0;
	data->option.status = 0;
	data->w = 0;
	data->h = 0;
	data->screen = 0;
	data->parse.nb_line = 0;
	data->parse.sizeline = 0;
	data->parse.check_map = FALSE;
	data->parse.check_c = FALSE;
	data->parse.check_f = FALSE;
	data->parse.check_r = FALSE;
	data->parse.check_s = FALSE;
	data->download_percent = 0;
	data->menu.i = 0;
	data->menu.button[0] = 1;
	data->menu.button[1] = 0;
	data->menu.button[2] = 0;
	i = -1;
	while (++i < HEIGHT / 2)
		data->ray.cur_dist[i] = HEIGHT / (HEIGHT - 2.0 * i);
	--i;
	while (++i < HEIGHT)
		data->ray.cur_dist[i] = HEIGHT / (2.0 * i - HEIGHT);
	init_filenames(data);
	init_img(data);
}

char	*g_monster[NB_MONSTER_IMG] =
{
	"./textures/monster/monster1.xpm",
	"./textures/monster/monster2.xpm",
	"./textures/monster/monster3.xpm",
	"./textures/monster/monster4.xpm",
	"./textures/monster/monster5.xpm",
	"./textures/monster/monster6.xpm",
	"./textures/monster/monster7.xpm",
	"./textures/monster/monster8.xpm",
};

char	*g_screamer[NB_SCREAMER_IMG] =
{
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-0.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-1.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-2.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-3.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-4.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-5.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-6.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-7.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-8.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-9.xpm",
	"./textures/screamer.xpm/34e1391c4f4f481fef9bcc26a895c566-10.xpm"
};

char	*g_door[NB_DOOR_IMG] =
{
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-0.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-1.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-2.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-3.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-4.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-5.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-6.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-7.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-8.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-9.xpm",
	"./textures/door/c9b6b9fb33aa4f1bd9e3dd1110b369c2-10.xpm"
};

char	*g_player2[NB_PLAYER2_IMG] =
{
	"./textures/player2.xpm/4533f2ff63b148a385f983582df1c743-0.xpm",
	"./textures/player2.xpm/4533f2ff63b148a385f983582df1c743-1.xpm",
	"./textures/player2.xpm/4533f2ff63b148a385f983582df1c743-2.xpm",
	"./textures/player2.xpm/4533f2ff63b148a385f983582df1c743-3.xpm"
};

char	*g_you_died[NB_YOU_DIED_IMG] = 
{
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-0.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-1.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-2.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-3.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-4.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-5.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-6.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-7.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-8.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-9.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-10.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-11.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-12.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-13.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-14.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-15.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-16.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-17.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-18.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-19.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-20.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-21.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-22.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-23.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-24.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-25.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-26.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-27.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-28.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-29.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-30.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-31.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-32.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-33.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-34.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-35.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-36.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-37.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-38.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-39.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-40.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-41.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-42.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-43.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-44.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-45.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-46.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-47.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-48.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-49.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-50.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-51.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-52.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-53.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-54.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-55.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-56.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-57.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-58.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-59.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-60.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-61.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-62.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-63.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-64.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-65.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-66.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-67.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-68.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-69.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-70.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-71.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-72.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-73.xpm",
	"./textures/you_died/8a64bacaa3d84e1cfde973528ca6f778-74.xpm"
};

char	*g_sword[NB_SWORD_IMG] =
{
	"./textures/sword/dba576cebbcd4badbff52554a162572a-0.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-1.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-2.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-3.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-4.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-5.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-6.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-7.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-8.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-9.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-10.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-11.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-12.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-13.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-14.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-15.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-16.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-17.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-18.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-17.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-16.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-15.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-14.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-13.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-12.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-11.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-10.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-9.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-8.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-7.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-6.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-5.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-4.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-3.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-2.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-1.xpm",
	"./textures/sword/dba576cebbcd4badbff52554a162572a-0.xpm"
};

char    *g_portal[NB_PORTAL_IMG] =
{
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-0.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-1.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-2.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-3.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-4.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-5.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-6.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-7.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-8.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-9.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-10.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-11.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-12.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-13.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-14.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-15.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-16.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-17.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-18.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-19.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-20.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-21.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-22.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-23.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-24.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-25.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-26.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-27.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-28.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-29.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-30.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-31.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-32.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-33.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-34.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-35.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-36.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-37.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-38.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-39.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-40.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-41.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-42.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-43.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-44.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-45.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-46.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-47.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-48.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-49.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-50.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-51.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-52.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-53.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-54.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-55.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-56.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-57.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-58.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-59.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-60.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-61.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-62.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-63.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-64.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-65.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-66.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-67.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-68.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-69.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-70.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-71.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-72.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-73.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-74.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-75.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-76.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-77.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-78.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-79.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-80.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-81.xpm",
	"./textures/portal.xpm/3be0da9b37e249c8bcf4fc4f6edc0979-82.xpm"
};
