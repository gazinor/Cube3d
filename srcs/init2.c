/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:27:49 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/06 08:56:35 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_gif_ptr(t_data *data, int i)
{
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
	i = -1;
	while (++i < NB_TP)
		data->tp[i].ptr = NULL;
}

void	init_gif_filename(t_data *data, int i)
{
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
	i = -1;
	while (++i < NB_TP)
		data->tp[i].filename = g_tp[i];
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
	data->spikes.filename = "./textures/spikes.xpm";
	data->plafond.filename = "./textures/plafond.xpm";
}

void	init_img(t_data *data)
{
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
	data->spikes.ptr = NULL;
}
