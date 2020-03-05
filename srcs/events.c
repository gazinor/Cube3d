/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 22:08:34 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 23:38:25 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_on(int key, t_data *data)
{
	if (data->event.menu == 1 || data->event.option == 1)
		return (0);
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

int		ft_move2(t_data *data)
{
	if (data->event.run == 1)
	{
		data->perso.rot = 0.0612;
		data->perso.speed = 0.158;
	}
	if (data->event.run == 0)
	{
		data->perso.rot = 0.0333;
		data->perso.speed = 0.086;
	}
	if (data->option.status == 1 && data->event.respawn == 1)
	{
		data->perso.pos.x = data->perso.depart.x;
		data->perso.pos.y = data->perso.depart.y;
	}
	if (data->event.screenshot == 1)
		screenshot(data);
	do_in_order(data);
	return (0);
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
	ft_move2(data);
	return (0);
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
