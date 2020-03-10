/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:58:49 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/10 02:16:38 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_data *data, void *ptr)
{
	if (ptr)
		mlx_destroy_image(data->mlx.ptr, ptr);
}

void	clean_gifs(t_data *data, int i)
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

void	clean_all(t_data *data)
{
	clean_gifs(data, -1);
	clean_images(data);
	free_img(data, data->mlx.win);
	free_tab(data->parse.map);
	free_tab(data->bonus.map);
	free_obj(data->door);
	free_obj(data->obj);
	free_obj(data->player);
	free_obj(data->monster_lst);
	free_obj(data->tp_lst);
	free_portal(data->portal_lst);
	write(1, "\n\n\e[32mToute les images ont ete effacees.\e[0m", 44);
}

int		exit_properly(t_data *data, t_bool error, char *error_msg)
{
	int	i;

	i = 0;
	data->signal = -1;
	pthread_join(data->t_download, NULL);
	pthread_join(data->t_monster, NULL);
	pthread_join(data->t_tp, NULL);
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
		data->begin == TRUE ? clean_all(data) : 0;
		exit(1);
	}
	data->begin == TRUE ? clean_all(data) : 0;
	write(1, "\n\e[32mCub3D s'est correctement eteint.\n\e[0m", 44);
	exit(0);
}
