/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:58:49 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/06 08:56:37 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_data *data, void *ptr)
{
	if (ptr)
		mlx_destroy_image(data->mlx.ptr, ptr);
}

void    clean_gifs(t_data *data, int i)
{
    while (++i < NB_PORTAL_IMG)
		free_img(data, data->portal[i].ptr);
    i = -1;
    while (++i < NB_SWORD_IMG)
		free_img(data, data->sword[i].ptr);
    i = -1;
    while (++i < NB_YOU_DIED_IMG)
		free_img(data, data->you_died[i].ptr);
    i = -1;
    while (++i < NB_PLAYER2_IMG)
		free_img(data, data->player2[i].ptr);
    i = -1;
    while (++i < NB_DOOR_IMG)
		free_img(data, data->gif_door[i].ptr);
    i = -1;
    while (++i < NB_SCREAMER_IMG)
		free_img(data, data->screamer[i].ptr);
    i = -1;
    while (++i < NB_MONSTER_IMG)
		free_img(data, data->monster[i].ptr);
    i = -1;
    while (++i < NB_TP)
		free_img(data, data->tp[i].ptr);
}

void	free_tab(char **map)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
}

void	clean_images(t_data *data)
{
	clean_gifs(data, -1);
	free_img(data, data->ntext.ptr);
	free_img(data, data->stext.ptr);
	free_img(data, data->etext.ptr);
	free_img(data, data->wtext.ptr);
	free_img(data, data->ciel.ptr);
	free_img(data, data->ciel_etoile.ptr);
	free_img(data, data->remote.ptr);
	free_img(data, data->sol.ptr);
	free_img(data, data->odoor.ptr);
	free_img(data, data->cdoor.ptr);
	free_img(data, data->i_menu.ptr);
	free_img(data, data->plafond.ptr);
	free_img(data, data->play_s_contour.ptr);
	free_img(data, data->play_uns_contour.ptr);
	free_img(data, data->option_s_contour.ptr);
	free_img(data, data->option_uns_contour.ptr);
	free_img(data, data->quit_s_contour.ptr);
	free_img(data, data->quit_uns_contour.ptr);
	free_img(data, data->retour_s.ptr);
	free_img(data, data->retour_uns.ptr);
	free_img(data, data->on_button.ptr);
	free_img(data, data->off_button.ptr);
	free_img(data, data->sprite.ptr);
	free_img(data, data->spikes.ptr);
	free_img(data, data->img.ptr);
	free_img(data, data->mlx.win);
	free_tab(data->parse.map);
	free_tab(data->bonus.map);
	printf("salut\n");
	free_obj(data->door);
	free_obj(data->obj);
	free_obj(data->player);
	free_obj(data->monster_lst);
	free_obj(data->tp_lst);
}

int		exit_properly(t_data *data, t_bool error, char *error_msg)
{
	int	i;

	i = 0;
	if (data->event.music == 1)
		system("killall afplay");
	if (error == TRUE)
	{
		write(2, "\n\e[31mErreur\n", 13);
		if (error_msg)
		{
			while (error_msg[i])
				++i;
			write(2, error_msg, i);
		}
		clean_images(data);
		exit(1);
	}
	clean_images(data);
	write(1, "\n\e[32mCub3D s'est correctement eteint.\n\e[0m", 44);
	exit(0);
}
