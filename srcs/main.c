/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 03:33:36 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

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
	else if (key == SLASH)
	{
		data->sword_index = 0;
		if (data->player && (data->player->sac.ray.mapx - data->perso.pos.x) *
				data->perso.dir.x < 1.3 && (data->player->sac.ray.mapy - data->perso.pos.y) *
				data->perso.dir.y < 1.3)
			data->event.hit[0] ^= 1;
		if (data->monster_lst && (data->monster_lst->sac.ray.mapx - data->perso.pos.x) *
				data->perso.dir.x < 1.3 && (data->monster_lst->sac.ray.mapy - data->perso.pos.y) *
				data->perso.dir.y < 1.3)
			data->event.hit[1] ^= 1;
		if (data->tp_lst && (data->tp_lst->sac.ray.mapx - data->perso.pos.x) *
				data->perso.dir.x < 1.3 && (data->tp_lst->sac.ray.mapy - data->perso.pos.y) *
				data->perso.dir.y < 1.3)
			data->event.hit[2] ^= 1;
	}
}

void	put_image_to_window(t_data *data)
{
	int		i;

	i = -1;
	if (data->life.blood > 0)
	{
		if (data->life.blood % 2 == 0)
			color_screen(data, 0xbb0a1e);
		else
			color_screen(data, 0x777777);
		--data->life.blood;
	}
	else
	{
		data->old_time = data->time.tv_usec + data->time.tv_sec * 1000000;
		gettimeofday(&data->time, NULL);
		data->anim += (data->time.tv_usec + data->time.tv_sec * 1000000) - data->old_time;
		if (data->option.status == 1 && data->sword_index < NB_SWORD_IMG)
		{
			print_sword(data, (int)data->sword_index);
			data->sword_index += 2.4765;
		}
		data->option.status == 1 ? print_life(data) : 1;
		if (data->map[(int)data->perso.pos.x][(int)data->perso.pos.y] == '5' &&
			data->screamer_index < NB_SCREAMER_IMG)
		{
			if ((int)data->screamer_index == 0)
			{
				if (data->anim % 2 == 1)
					system("afplay sounds/ah_oui_daccord.mp3 &");
				system("afplay sounds/screamer.mp3 &");
			}
			if ((int)data->screamer_index == 8 && data->anim % 2 == 0)
				system("afplay sounds/tufousmagueuletoi.mp3 &");
			print_screamer(data, (int)data->screamer_index);
			if ((int)data->screamer_index == NB_SCREAMER_IMG - 1)
				data->life.hurt = data->life.max_life;
			data->screamer_index += 0.6;
		}
		else if (data->life.alive == FALSE && data->you_died_index < NB_YOU_DIED_IMG)
		{
			you_died(data);	
			if (++data->you_died_index == NB_YOU_DIED_IMG)
				menu(data);
		}
		else if (data->anim < 1500000.0)
			while (++i < HEIGHT * WIDTH)
				data->img.buffer[i] = dark(data->img.buffer[i],
						data->anim / 1500000.0);
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
}

void	do_in_order(t_data *data)
{ 
	char 	*ret = NULL;

	check_mod(data);
	crt_img(data);
	if (data->option.status == 1)
		if (data->door)
		{
			if (data->door->sac.ray.walldist > 1.8 && data->door_index < NB_DOOR_IMG - 1)
				++data->door_index;
			else if (data->door->sac.ray.walldist < 1.8 && data->door_index > 0)
				--data->door_index;
			if (data->door_index != NB_DOOR_IMG - 1)
			{
				system("echo \"open door\" | nc localhost 13000");
				data->event.door = 1;
			}
			else if (data->door_index == NB_DOOR_IMG - 1 && data->event.door !=
					0 && data->map[(int)data->perso.pos.x][(int)data->perso.pos.y] != '4')
				data->event.door = 0;
			print_door(data, data->door, data->gif_door[(int)data->door_index]);
			free_obj(data->door);
			data->door = NULL;
		}
	if (data->obj)
	{
		print_obj(data, data->obj);
		free_obj(data->obj);
		data->obj = NULL;
	}	
	pthread_mutex_lock(&data->mutex_player);
	if (data->player)
	{
		print_obj(data, data->player);
		free_obj(data->player);
		data->player = NULL;
	}	
	if (data->tp_lst)
		print_obj(data, data->tp_lst);
	if (data->monster_lst)
		print_obj(data, data->monster_lst);
	if (data->map[(int)data->perso.pos.x][(int)data->perso.pos.y] == 'x')
		data->life.hurt += 0.01 * data->life.max_life;
	pthread_mutex_unlock(&data->mutex_player);
	if (check_portal(data, data->perso.pos.x, data->perso.pos.y) == TRUE)
	{
		data->perso.dir = set_dir_portal(data->map[(int)data->perso.pos.x][(int)data->perso.pos.y]);
		data->perso.pos.x += (data->perso.dir.x * 3);
		data->perso.pos.y += (data->perso.dir.y * 3);
		data->perso.planx = 0.66 * data->perso.dir.y;
		data->perso.plany = -0.66 * data->perso.dir.x;
		data->anim = 0;
	}
	if (data->portal_lst)
	{
		data->portal_index = (int)(data->portal_index + 1) % NB_PORTAL_IMG;
		print_portal(data, data->portal_lst, data->portal_index);
		free_portal(data->portal_lst);
		data->portal_lst = NULL;
	}
	if (data->screen == 1)
	{
		screenshot(data);
		exit_properly(data, 0, "Screenshot effectue.\n");
	}
	ret = serialized(data);
	if (ret)
	{
		system(ret);
		free(ret);
		ret = NULL;
	}
	if (data->life.max_life <= data->life.hurt && data->life.alive == TRUE)
	{
		data->anim = 0;
		data->life.alive = FALSE;
	}
	put_image_to_window(data);
}

int		main(int ac, char **av)
{
	t_data		data;
	pthread_t	thread;
	pthread_t	download;
	pthread_t	monster;
	pthread_t	tp;

	if (ac != 3 && ac != 2)
	{
		write(2, "\e[31mErreur\n", 12);
		write(2, "Mauvais nombre d'arguments.\n", 28);
		exit(0);
	}
	ft_init(&data);
	data.launch = FALSE;
	data.mlx.ptr = mlx_init();
	data.img.ptr = mlx_new_image(data.mlx.ptr, WIDTH, HEIGHT);
	data.img.buffer = (int*)mlx_get_data_addr(data.img.ptr, &data.img.bpp,
			&data.img.size, &data.img.endian);
	pthread_mutex_init(&data.mutex_player, NULL);
	pthread_create(&download, NULL, draw_downloading, &data);
	pthread_create(&thread, NULL, t_loop, &data);
	pthread_create(&tp, NULL, do_tp, &data);
	pthread_create(&monster, NULL, use_monsters, &data);
	parsing(av[1], &data);
	load_background(&data);
	load_dir_textures(&data);
	load_objs(&data);
	load_portal(&data);
	load_sword(&data);
	load_you_died(&data);
	load_player2(&data);
	load_screamer(&data);
	load_monster(&data);
	load_tp(&data);
	load_door(&data);
	load_menu(&data);
	load_option(&data);
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "-save") == TRUE ||
				ft_strcmp(av[2], "--save") == TRUE)
		{
			data.screen = 1;
			init_normale(&data);
			do_in_order(&data);
		}
		else
			exit_properly(&data, 1, "Unknown argument.\n");
	}
	if (data.screen == 0)
		data.mlx.win = mlx_new_window(data.mlx.ptr, WIDTH, HEIGHT, "Cub3d");
	system("afplay sounds/bgm.mp3 &");
	data.event.music = 1;
	menu(&data);
	return (0);
}
