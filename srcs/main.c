/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/09 02:44:43 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int		exit_properly(t_bool error, char *error_msg)
{
	int	i;

	i = 0;
	if (error == TRUE)
{
		while (error_msg[i])
			++i;
		write(2, error_msg, i);
		exit(1);
	}
	exit(0);
}

int		key(int key, t_data *data)
{
	printf("%d\n", key);
	if (key == ESC)
		exit_properly(FALSE, NULL);
	else if (key == FORWARD)
		data->event.forward ^= 1;
	else if (key == BACKWARD)
		data->event.backward ^= 1;
	else if (key == RIGHT)
		data->event.right ^= 1;
	else if (key == LEFT)
		data->event.left ^= 1;
	else if (key == R_ARROW)
		data->event.r_arrow ^= 1;
	else if (key == L_ARROW)
		data->event.l_arrow ^= 1;
	else if (key == DOOR)
		data->event.door ^= 1;
	else if (key == RUN)
		data->event.run ^= 1;
	return (0);
}

void	put_image_to_window(t_data *data)
{
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->ciel.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->sol.ptr, 0, HEIGHT/2);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
}

int		ft_move(t_data *data)
{
	if (data->event.forward == 1)
		move_forward(data);
	if (data->event.backward == 1)
		move_backward(data);
	if (data->event.right == 1)
		move_right(data);
	if (data->event.left == 1)
		move_left(data);
	if (data->event.r_arrow == 1)
		turn_right(data);
	if (data->event.l_arrow == 1)
		turn_left(data);
	if (data->event.door == 1 && data->map[(int)(data->perso.pos.x + 
			(data->perso.dir.x * data->perso.speed))][(int)(data->perso.pos.y + 
						(data->perso.dir.y * data->perso.speed))] == '3')
		data->map[(int)(data->perso.pos.x + (data->perso.dir.x *
					data->perso.speed))][(int)(data->perso.pos.y + 
								(data->perso.dir.y * data->perso.speed))] = '0';
	if (data->event.run == 1)
		data->perso.speed = 0.118;
	if (data->event.run == 0 && data->perso.speed != 0.066)
		data->perso.speed = 0.086;
	crt_img(data);
	put_image_to_window(data);
	return (0);
}

void	crt_window(t_data *data)
{
	data->mlx.ptr = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.ptr, WIDTH, HEIGHT, "Cub3d");
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
										&data->img.size, &data->img.endian);
}

void	load_background(t_data *data)
{
	data->ciel.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/ciel.xpm",
						&(data->ciel.width), &(data->ciel.height));
	data->sol.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/sol.xpm",
						&(data->sol.width), &(data->sol.height));
	data->tmp_ciel = resize_image(data, &data->ciel, WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->ciel.ptr);
	data->ciel = data->tmp_ciel;
	data->tmp_sol = resize_image(data, &data->sol, WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->sol.ptr);
	data->sol = data->tmp_sol;
}

void	load_textures(t_data *data)
{
	data->ntext.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/ntext.xpm",
						&(data->ntext.width), &(data->ntext.height));
	data->stext.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/stext.xpm",
						&(data->stext.width), &(data->stext.height));
	data->etext.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/etext.xpm",
						&(data->etext.width), &(data->etext.height));
	data->wtext.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/wtext.xpm",
						&(data->wtext.width), &(data->wtext.height));
	data->tmp_ntext = resize_image(data, &data->ntext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->ntext.ptr);
	data->ntext = data->tmp_ntext;
	data->tmp_stext = resize_image(data, &data->stext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->stext.ptr);
	data->stext = data->tmp_stext;
	data->tmp_etext = resize_image(data, &data->etext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->etext.ptr);
	data->etext = data->tmp_etext;
	data->tmp_wtext = resize_image(data, &data->wtext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->wtext.ptr);
	data->wtext = data->tmp_wtext;
}

int		main(void)
{
	t_data data;

	ft_init(&data);
	crt_window(&data);
	load_background(&data);
	load_textures(&data);
	mlx_do_key_autorepeatoff(data.mlx.ptr);
	mlx_hook(data.mlx.win, KEYDOWN, 0, key, &data);
	mlx_hook(data.mlx.win, KEYUP, 0, key, &data);
	mlx_hook(data.mlx.win, QUIT, 0, exit_properly, &data);
	mlx_loop_hook(data.mlx.ptr, ft_move, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
