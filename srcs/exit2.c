/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 02:07:52 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/10 02:16:55 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_images(t_data *data)
{
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
}
