/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_in_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 05:34:05 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/08 23:26:54 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	third_order(t_data *data, char *ret)
{
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
}

void	second_order(t_data *data)
{
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
		data->perso.dir = set_dir_portal(data->map[(int)data->perso.pos.x][
				(int)data->perso.pos.y]);
		data->perso.pos.x += (data->perso.dir.x * 3);
		data->perso.pos.y += (data->perso.dir.y * 3);
		data->perso.planx = 0.66 * data->perso.dir.y;
		data->perso.plany = -0.66 * data->perso.dir.x;
		data->anim = 0;
	}
}

void	door(t_data *data)
{
	if (data->door)
	{
		if (data->door->sac.ray.walldist > 1.8 &&
				data->door_index < NB_DOOR_IMG - 1)
			++data->door_index;
		else if (data->door->sac.ray.walldist < 1.8 &&
				data->door_index > 0)
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
}

void	do_in_order(t_data *data)
{
	char	*ret;

	check_mod(data);
	crt_img(data);
	if (data->option.status == 1)
		door(data);
	if (data->obj)
	{
		print_obj(data, data->obj);
		free_obj(data->obj);
		data->obj = NULL;
	}
	second_order(data);
	third_order(data, ret = NULL);
	put_image_to_window(data);
}
