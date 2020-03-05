/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 21:58:49 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 22:06:40 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_img(t_data *data, void *ptr)
{
	if (ptr)
		mlx_destroy_image(data->mlx.ptr, ptr);
}

void	clean_images(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_PORTAL_IMG)
		free_img(data, data->portal[i].ptr);
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
	free_img(data, data->img.ptr);
	free_img(data, data->mlx.win);
}

int		exit_properly(t_data *data, t_bool error, char *error_msg)
{
	int	i;

	i = 0;
//	write(error == TRUE ? 2 : 1, "\n", 1);
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
