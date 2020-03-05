/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:04:23 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 07:20:13 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_data *data, t_img *img, int width, int height)
{
	t_img	tmp;

	img->ptr = mlx_xpm_file_to_image(data->mlx.ptr, img->filename,
			&(img->width), &(img->height));
	if (img->ptr == 0)
		exit_properly(data, 1, "ouverture d'une image impossible\n");
	tmp = resize_image(data, img, width, height);
	mlx_destroy_image(data->mlx.ptr, img->ptr);
	*img = tmp;
	img->check = TRUE;
	data->download_percent += 0.25796;
}

void	load_background(t_data *data)
{
	load_image(data, &data->ciel, 9 * data->h, data->h / 2);
	load_image(data, &data->sol, 1000, 1000);
	load_image(data, &data->ciel_etoile, 9 * data->h, data->h / 2);
	load_image(data, &data->plafond, 1000, 1000);
}

void	load_dir_textures(t_data *data)
{
	load_image(data, &data->ntext, 1000, 1000);
	load_image(data, &data->stext, 1000, 1000);
	load_image(data, &data->etext, 1000, 1000);
	load_image(data, &data->wtext, 1000, 1000);
}

void	load_objs(t_data *data)
{
	load_image(data, &data->cdoor, 500, 1000);
	load_image(data, &data->odoor, 500, 1000);
	load_image(data, &data->remote, data->w / 2, data->h / 2);
	load_image(data, &data->sprite, 1000, 1000);
	load_image(data, &data->spikes, 1000, 1000);
}
