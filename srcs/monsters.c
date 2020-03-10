/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monsters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 05:00:52 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/09 23:26:53 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	intern_monsters(t_data *data, double *x, double *y, int *life)
{
	pthread_mutex_lock(&data->mutex_player);
	if (!data->monster_lst)
		create_obj(data, &data->monster_lst, data->monster[
				(int)data->monster_index % NB_MONSTER_IMG], 0);
	data->monster_index += 1;
	data->monster_lst->sac.img = data->monster[(int)data->monster_index %
		NB_MONSTER_IMG];
	data->monster_lst->sac.ray.mapx = *x;
	data->monster_lst->sac.ray.mapy = *y;
	data->monster_lst->sac.ray.walldist = sqrt((data->perso.pos.x - 0.5 - *x)
		* (data->perso.pos.x - 0.5 - *x) + (data->perso.pos.y - 0.5 - *y)
		* (data->perso.pos.y - 0.5 - *y));
	*x += (data->perso.pos.x - 0.5 - data->monster_lst->sac.ray.mapx) /
data->monster_lst->sac.ray.walldist * 0.105;
	*y += (data->perso.pos.y - 0.5 - data->monster_lst->sac.ray.mapy) /
data->monster_lst->sac.ray.walldist * 0.105;
	pthread_mutex_unlock(&data->mutex_player);
	if (data->event.hit[1] == TRUE && --*life != -1)
		data->event.hit[1] = FALSE;
}

int		condition_monsters(t_data *data, int *life, double *x, double *y)
{
	if (data->launch == FALSE)
	{
		free_obj(data->monster_lst);
		data->monster_lst = NULL;
		return (0);
	}
	intern_monsters(data, x, y, life);
	if (*life <= 0)
	{
		free(data->monster_lst);
		data->monster_lst = NULL;
		return (0);
	}
	return (1);
}

void	*use_monsters(void *arg)
{
	t_data		*data;
	double		x;
	double		y;
	int			life;

	data = (t_data *)arg;
	while (data->tp_index != -1 && data->signal != -1)
	{
		x = 2.;
		y = 2.;
		life = 3;
		while (data->signal != -1)
		{
			if (!condition_monsters(data, &life, &x, &y))
				break ;
			if (data->monster_lst->sac.ray.walldist < 0.5)
			{
				data->life.hurt += (0.08 * data->life.max_life);
				data->life.blood += 0.5;
			}
			usleep(100000);
		}
		data->signal != -1 ? usleep(3000000) : 0;
	}
	return (NULL);
}
