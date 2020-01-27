/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:17:45 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/27 00:30:30 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x + (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y + (data->perso.dir.y * data->perso.speed));
	if (data->map[(int)new_x][(int)data->perso.pos.y] == '0' ||
			(data->map[(int)new_x][(int)data->perso.pos.y] == '4' &&
					data->event.door == 1))
		data->perso.pos.x = new_x;
	if (data->map[(int)data->perso.pos.x][(int)new_y] == '0' ||
			(data->map[(int)data->perso.pos.x][(int)new_y] == '4' &&
					data->event.door == 1))
		data->perso.pos.y = new_y;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x - (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y - (data->perso.dir.y * data->perso.speed));
	if (data->map[(int)new_x][(int)data->perso.pos.y] == '0' ||
			(data->map[(int)new_x][(int)data->perso.pos.y] == '4' &&
					data->event.door == 1))
		data->perso.pos.x = new_x;
	if (data->map[(int)data->perso.pos.x][(int)new_y] == '0' ||
			(data->map[(int)data->perso.pos.x][(int)new_y] == '4' &&
					data->event.door == 1))
		data->perso.pos.y = new_y;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x) + (data->perso.dir.y * data->perso.speed);
	new_y = (data->perso.pos.y - (data->perso.dir.x * data->perso.speed));
	if (data->map[(int)new_x][(int)data->perso.pos.y] == '0' ||
			(data->map[(int)new_x][(int)data->perso.pos.y] == '4' &&
					data->event.door == 1))
		data->perso.pos.x = new_x;
	if (data->map[(int)data->perso.pos.x][(int)new_y] == '0' ||
			(data->map[(int)data->perso.pos.x][(int)new_y] == '4' &&
					data->event.door == 1))
		data->perso.pos.y = new_y;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x) - (data->perso.dir.y * data->perso.speed);
	new_y = (data->perso.pos.y + (data->perso.dir.x * data->perso.speed));
	if (data->map[(int)new_x][(int)data->perso.pos.y] == '0' ||
			(data->map[(int)new_x][(int)data->perso.pos.y] == '4' &&
					data->event.door == 1))
		data->perso.pos.x = new_x;
	if (data->map[(int)data->perso.pos.x][(int)new_y] == '0' ||
			(data->map[(int)data->perso.pos.x][(int)new_y] == '4' &&
					data->event.door == 1))
		data->perso.pos.y = new_y;
}
