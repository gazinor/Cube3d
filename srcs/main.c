/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/06 08:23:47 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int		exit_properly(t_data *data, t_bool error, char *error_msg)
{
	int	i;

	i = 0;
	system("killall afplay");
	mlx_destroy_image(data->mlx.ptr, data->ntext.ptr);
	mlx_destroy_image(data->mlx.ptr, data->stext.ptr);
	mlx_destroy_image(data->mlx.ptr, data->etext.ptr);
	mlx_destroy_image(data->mlx.ptr, data->wtext.ptr);
	mlx_destroy_image(data->mlx.ptr, data->ciel.ptr);
	mlx_destroy_image(data->mlx.ptr, data->ciel_etoile.ptr);
	mlx_destroy_image(data->mlx.ptr, data->remote.ptr);
	mlx_destroy_image(data->mlx.ptr, data->sol.ptr);
	mlx_destroy_image(data->mlx.ptr, data->odoor.ptr);
	mlx_destroy_image(data->mlx.ptr, data->cdoor.ptr);
	mlx_destroy_image(data->mlx.ptr, data->img.ptr);
	mlx_destroy_window(data->mlx.ptr, data->mlx.win);
	if (error == TRUE)
{
		while (error_msg[i])
			++i;
		write(2, error_msg, i);
		exit(1);
	}
	exit(0);
}

void	intern_key(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(data, FALSE, NULL);
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
	else if (key == RUN)
		data->event.run ^= 1;
	else if (key == RESPAWN)
		data->event.respawn ^= 1;
	else if (key == SCREENSHOT)
		data->event.screenshot ^= 1;
}

int		key_on(int key, t_data *data)
{
	if (key == DOOR && data->map[(int)data->perso.pos.x]
			[(int)data->perso.pos.y] != '4')
		data->event.door ^= 1;
	else if (key == TAB)
		data->mod.nbr[data->mod.i % 3] ^= 1;
	else
		intern_key(key, data);
	return (0);
}

int		key_off(int key, t_data *data)
{
	if (key == TAB)
		data->mod.nbr[++data->mod.i % 3] ^= 1;
	else
		intern_key(key, data);
	return (0);
}

void	put_image_to_window(t_data *data)
{
	if (data->mod.nbr[DARK] == 1)
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->ciel_etoile.ptr, 0, 0);
	else
		mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->ciel.ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.ptr,
	data->mlx.win, data->sol.ptr, 0, HEIGHT / 2);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	if (data->event.door == 1)
		mlx_put_image_to_window(data->mlx.ptr,
				data->mlx.win, data->remote.ptr, WIDTH / 2, HEIGHT / 2);
}

void	check_door(t_data *data)
{
	if (data->map[(int)(data->perso.pos.x + (data->perso.dir.x *
			data->perso.speed))][(int)(data->perso.pos.y +
			(data->perso.dir.y * data->perso.speed))] == '3')
		data->map[(int)(data->perso.pos.x + (data->perso.dir.x *
			data->perso.speed))][(int)(data->perso.pos.y + 
			(data->perso.dir.y * data->perso.speed))] = '0';
}

void	check_mod(t_data *data)
{
	if (data->mod.nbr[NORMAL] == 1 && data->mod.light != 5)
		data->mod.light = 5;
	if (data->mod.nbr[DARK] == 1 && data->mod.light != 1)
		data->mod.light = 0.5;
	if (data->mod.nbr[MIRROR] == 1 && data->mod.light != 5)
		data->mod.light = 5;
}

void	do_in_order(t_data *data)
{
	check_mod(data);
	crt_img(data);
	if (data->door)
	{
		print_door(data, data->door);
		free_obj(data->door);
		data->door = NULL;
	}
	if (data->obj)
	{
		print_obj(data, data->obj);
		free_obj(data->obj);
		data->obj = NULL;
	}
	put_image_to_window(data);
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
	if (data->event.door == 1)
		check_door(data);
	if (data->event.run == 1)
		data->perso.speed = 0.158;
	if (data->event.run == 0)
		data->perso.speed = 0.086;
	if (data->event.respawn == 1)
	{
		data->perso.pos.x = data->perso.depart.x;
		data->perso.pos.y = data->perso.depart.y;
	}
	if (data->event.screenshot == 1)
		screenshot(data);
	do_in_order(data);
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
	data->ciel_etoile.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
					"./textures/ciel_etoile.xpm", 
					&(data->ciel_etoile.width), &(data->ciel_etoile.height));
	data->tmp_ciel = resize_image(data, &data->ciel, WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->ciel.ptr);
	data->ciel = data->tmp_ciel;
	data->tmp_sol = resize_image(data, &data->sol, WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->sol.ptr);
	data->sol = data->tmp_sol;
	data->tmp_ciel_etoile = resize_image(data, &data->ciel_etoile,
	WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->ciel_etoile.ptr);
	data->ciel_etoile = data->tmp_ciel_etoile;
}

void	load_dir_textures(t_data *data)
{
	data->ntext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/ntext.xpm", &(data->ntext.width), &(data->ntext.height));
	data->stext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/stext.xpm", &(data->stext.width), &(data->stext.height));
	data->etext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/etext.xpm", &(data->etext.width), &(data->etext.height));
	data->wtext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/wtext.xpm", &(data->wtext.width), &(data->wtext.height));
	data->tmp_ntext = resize_image(data, &data->ntext, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->ntext.ptr);
	data->ntext = data->tmp_ntext;
	data->tmp_stext = resize_image(data, &data->stext, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->stext.ptr);
	data->stext = data->tmp_stext;
	data->tmp_etext = resize_image(data, &data->etext, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->etext.ptr);
	data->etext = data->tmp_etext;
	data->tmp_wtext = resize_image(data, &data->wtext, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->wtext.ptr);
	data->wtext = data->tmp_wtext;
}

void	load_objs(t_data *data)
{
	data->cdoor.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/cdoor.xpm", &(data->cdoor.width), &(data->cdoor.height));
	data->tmp_cdoor = resize_image(data, &data->cdoor, 500, 1000);
	mlx_destroy_image(data->mlx.ptr, data->cdoor.ptr);
	data->cdoor = data->tmp_cdoor;
	data->odoor.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/odoor.xpm", &(data->odoor.width), &(data->odoor.height));
	data->tmp_odoor = resize_image(data, &data->odoor, 500, 1000);
	mlx_destroy_image(data->mlx.ptr, data->odoor.ptr);
	data->odoor = data->tmp_odoor;
	data->remote.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/remote.xpm", &(data->remote.width), &(data->remote.height));
	data->tmp_remote = resize_image(data, &data->remote, WIDTH/2, HEIGHT/2);
	mlx_destroy_image(data->mlx.ptr, data->remote.ptr);
	data->remote = data->tmp_remote;
	data->sprite.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
		"./textures/sprite.xpm", &(data->sprite.width), &(data->sprite.height));
	data->tmp_sprite = resize_image(data, &data->sprite, 1000, 1000);
	mlx_destroy_image(data->mlx.ptr, data->sprite.ptr);
	data->sprite = data->tmp_sprite;
}

void	loop(t_data *data)
{
	mlx_do_key_autorepeatoff(data->mlx.ptr);
	mlx_hook(data->mlx.win, KEYDOWN, 0, key_on, data);
	mlx_hook(data->mlx.win, KEYUP, 0, key_off, data);
	mlx_hook(data->mlx.win, QUIT, 0, exit_properly, data);
	mlx_loop_hook(data->mlx.ptr, ft_move, data);
	mlx_loop(data->mlx.ptr);
}

int		main(void)
{
	t_data data;

	ft_init(&data);
	crt_window(&data);
	load_background(&data);
	load_dir_textures(&data);
	load_objs(&data);
	load_menu(&data);
	system("afplay sounds/bgm.mp3 &");
	menu(&data);
	return (0);
}
