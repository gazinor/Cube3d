/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:18:38 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/04 22:24:49 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void    turn_left(t_data *data)
{
	double  new_x;
	double  new_y;
	double  new_plan_x;
	double  new_plan_y;

	new_x = data->perso.dir.x * cos(data->perso.rot) +
		data->perso.dir.y * sin(data->perso.rot);
	new_y = data->perso.dir.y * cos(data->perso.rot) -
		data->perso.dir.x * sin(data->perso.rot);
	new_plan_x = data->perso.planx * cos(data->perso.rot) +
		data->perso.plany * sin(data->perso.rot);
	new_plan_y = data->perso.plany * cos(data->perso.rot) -
		data->perso.planx * sin(data->perso.rot);
	data->perso.dir.x = new_x;
	data->perso.dir.y = new_y;
	data->perso.planx = new_plan_x;
	data->perso.plany = new_plan_y;
}

void    turn_right(t_data *data)
{
	double  new_x;
	double  new_y;
	double  new_plan_x;
	double  new_plan_y;

	new_x = data->perso.dir.x * cos(data->perso.rot) -
		data->perso.dir.y * sin(data->perso.rot);
	new_y = data->perso.dir.y * cos(data->perso.rot) +
		data->perso.dir.x * sin(data->perso.rot);
	new_plan_x = data->perso.planx * cos(data->perso.rot) -
		data->perso.plany * sin(data->perso.rot);
	new_plan_y = data->perso.plany * cos(data->perso.rot) +
		data->perso.planx * sin(data->perso.rot);
	data->perso.dir.x = new_x;
	data->perso.dir.y = new_y;
	data->perso.planx = new_plan_x;
	data->perso.plany = new_plan_y;
}
