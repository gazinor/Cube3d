/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 06:05:12 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

void	slash(int key, t_data *(data))
{
	if (key == SLASH)
	{
		data->sword_index = 0;
		if (data->player && (data->player->sac.ray.mapx - data->perso.pos.x) *
data->perso.dir.x < 1.3 && (data->player->sac.ray.mapy - data->perso.pos.y) *
				data->perso.dir.y < 1.3)
			data->event.hit[0] ^= 1;
		if (data->monster_lst && (data->monster_lst->sac.ray.mapx -
				data->perso.pos.x) * data->perso.dir.x < 1.3 &&
(data->monster_lst->sac.ray.mapy - data->perso.pos.y) * data->perso.dir.y < 1.3)
			data->event.hit[1] ^= 1;
		if (data->tp_lst && (data->tp_lst->sac.ray.mapx - data->perso.pos.x) *
data->perso.dir.x < 1.3 && (data->tp_lst->sac.ray.mapy - data->perso.pos.y) *
				data->perso.dir.y < 1.3)
			data->event.hit[2] ^= 1;
	}
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
	else
		slash(key, data);
}

void	intern_put_img_to_win(t_data *data, int i)
{
	if (data->life.alive == FALSE && data->you_died_index < NB_YOU_DIED_IMG)
	{
		you_died(data);
		if (++data->you_died_index == NB_YOU_DIED_IMG)
			menu(data);
	}
	else if (data->map[(int)data->perso.pos.x][(int)data->perso.pos.y] == '5' &&
		data->screamer_index < NB_SCREAMER_IMG)
	{
		if ((int)data->screamer_index == 0)
			system((data->anim % 2 == 1) ?
	"afplay sounds/ah_oui_daccord.mp3 &" : "afplay sounds/screamer.mp3 &");
		if ((int)data->screamer_index == 8 && data->anim % 2 == 0)
			system("afplay sounds/tufousmagueuletoi.mp3 &");
		print_screamer(data, (int)data->screamer_index);
		if ((int)data->screamer_index == NB_SCREAMER_IMG - 1)
			data->life.hurt = data->life.max_life;
		data->screamer_index += 0.6;
	}
	else if (data->anim < 1500000.0)
		while (++i < HEIGHT * WIDTH)
			data->img.buffer[i] = dark(data->img.buffer[i],
					data->anim / 1500000.0);
}

void	put_image_to_window(t_data *data)
{
	int		i;

	i = -1;
	if (data->life.blood > 0)
	{
		color_screen(data, ((int)data->life.blood % 2 == 0) ?
					0xbb0a1e : 0x777777);
		--data->life.blood;
	}
	else
	{
		data->old_time = data->time.tv_usec + data->time.tv_sec * 1000000;
		gettimeofday(&data->time, NULL);
		data->anim += (data->time.tv_usec + data->time.tv_sec * 1000000) -
			data->old_time;
		if (data->option.status == 1 && data->sword_index < NB_SWORD_IMG)
		{
			print_sword(data, (int)data->sword_index);
			data->sword_index += 2.4765;
		}
		data->option.status == 1 ? print_life(data) : 1;
		intern_put_img_to_win(data, i);
	}
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
}

int		main(int ac, char **av)
{
	t_data		data;

	launch_program(&data, ac, av);
	load_all(&data);
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "-save") == TRUE ||
				ft_strcmp(av[2], "--save") == TRUE)
		{
			data.screen = 1;
			init_normale(&data);
			do_in_order(&data);
		}
		exit_properly(&data, 1, "Unknown argument.\n");
	}
	if (data.screen == 0)
		data.mlx.win = mlx_new_window(data.mlx.ptr, WIDTH, HEIGHT, "Cub3d");
	system("afplay sounds/bgm.mp3 &");
	data.event.music = 1;
	menu(&data);
	return (0);
}
