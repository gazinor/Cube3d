/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/24 09:48:00 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

void	free_img(t_data *data, void *ptr)
{
	if (ptr)
		mlx_destroy_image(data->mlx.ptr, ptr);
}

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
	free_img(data, data->img.ptr);
	free_img(data, data->mlx.win);
}

int		exit_properly(t_data *data, t_bool error, char *error_msg)
{
	int	i;

	i = 0;
	if (data->event.music == 1)
		system("killall afplay");
	(void)data;
	if (error == TRUE)
	{
		write(2, "\e[31mErreur\n", 12);
		while (error_msg[i])
			++i;
		write(2, error_msg, i);
		clean_images(data);
		exit(1);
	}
	clean_images(data);
	write(1, "\e[32mCub3D s'est correctement eteint.\n\e[0m", 37);
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
	if (data->event.menu == 1 || data->event.option == 1)
		return (0);
	if (key == DOOR && data->map[(int)data->perso.pos.x]
[(int)data->perso.pos.y] != '4' && data->option.status == 1)
		data->event.door ^= 1;
	else if (key == TAB && data->option.status == 1)
		data->mod.nbr[data->mod.i % 3] ^= 1;
	else
		intern_key(key, data);
	return (0);
}

int		key_off(int key, t_data *data)
{
	if (data->event.menu == 1 || data->event.option == 1)
		return (0);
	if (key == TAB && data->option.status == 1)
		data->mod.nbr[++data->mod.i % 3] ^= 1;
	else if (key == MENU)
		data->event.menu = 1;
	else
		intern_key(key, data);
	return (0);
}

void	put_image_to_window(t_data *data)
{
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
	if (data->option.status == 1)
	{
		if (data->mod.nbr[NORMAL] == 1 && data->mod.light != 5)
			data->mod.light = 5;
		if (data->mod.nbr[DARK] == 1 && data->mod.light != 1)
			data->mod.light = 0.5;
		if (data->mod.nbr[MIRROR] == 1 && data->mod.light != 5)
			data->mod.light = 5;
	}
}

void	do_in_order(t_data *data)
{ 
	check_mod(data);
	crt_img(data);
	if (data->option.status == 1)
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
	if (data->event.menu == 1)
		menu(data);
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
}

void	load_background(t_data *data)
{
	load_image(data, &data->ciel, 9 * HEIGHT, HEIGHT / 2);
	load_image(data, &data->sol, WIDTH, HEIGHT / 2);
	load_image(data, &data->ciel_etoile, 9 * HEIGHT, HEIGHT / 2);
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
	load_image(data, &data->remote, WIDTH / 2, HEIGHT / 2);
	load_image(data, &data->sprite, 1000, 1000);
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

int		main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (0);
	crt_window(&data);
	ft_init(&data);
	parsing(av[1], &data);
	load_background(&data);
	load_dir_textures(&data);
	load_objs(&data);
	load_menu(&data);
	load_option(&data);
	data.event.music = system("afplay sounds/bgm.mp3 &");
	menu(&data);
	return (0);
}
