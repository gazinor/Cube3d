/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/04 20:57:26 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

char	*G_BUFFER[11] =
{
	"1111111111111",
	"1001000000001",
	"100N000010001",
	"1000000000001",
	"1010000001001",
	"1000000100001",
	"1000001010001",
	"1000000100001",
	"1000000001001",
	"1111111111111"
};

void	*ft_init_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (G_BUFFER[i])
		i++;
	if (!(data->map = malloc(sizeof(char*) * i + 1)))
		return (NULL);
	i = 0;
	while (G_BUFFER[i])
	{
		j = 0;
		while (G_BUFFER[i][j])
			j++;
		if (!(data->map[i] = malloc(sizeof(char) * j + 1)))
			return (NULL);
		i++;
	}
	ft_fill_map(data);
	return ((void*)0);
}

void	ft_fill_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (G_BUFFER[i])
	{
		j = 0;
		while (G_BUFFER[i][j])
		{
			data->map[i][j] = G_BUFFER[i][j];
			if (G_BUFFER[i][j] == 'N' || G_BUFFER[i][j] == 'S' ||
			G_BUFFER[i][j] == 'E' || G_BUFFER[i][j] == 'O')
			{
				data->map[i][j] = '0';
				data->perso.pos.x = (double)i + 0.5;
				data->perso.pos.y = (double)j + 0.5;
			}
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
}

/*
** angle = 70;
** data->perso.dir.x = data->perso.rot - (2 * (angle / 180) - 1)
** data->perso.rot + (2 * (angle / 180) - 1)
*/

int		exit_properly(t_bool error, char *error_msg)
{
	int		i;

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

/*
** distance mur en face : (WIDTH / 2) / tan(35 * M_PI / 180);
** start = (HEIGHT / 2) - ((HEIGHT / 2) / dist)
** end = (HEIGHT / 2) + ((HEIGHT / 2) / dist)
*/

void		*crt_img(t_data *data)
{
	int x;

	x = -1;
	while (++x < WIDTH)
	{
		raycasting(data, x);
		crt_column(data, x);
	}
	return (data->img.buffer);
}

void		crt_column(t_data *data, int column)
{
	int	i;

	i = -1;
	while (++i < data->ray.start)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFFFF;
	i--;
	while (++i < data->ray.end)
	{
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFF0000;
	}
	i--;
	while (++i < HEIGHT)
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xA0AAAAAA;
}

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x + (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y + (data->perso.dir.y * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)data->perso.pos.y] == '0')
        data->perso.pos.x = new_x;
    if (data->map[(int)data->perso.pos.x][(int)new_y] == '0')
        data->perso.pos.y = new_y;
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x - (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y - (data->perso.dir.y * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)data->perso.pos.y] == '0')
        data->perso.pos.x = new_x;
    if (data->map[(int)data->perso.pos.x][(int)new_y] == '0')
        data->perso.pos.y = new_y;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x) + (data->perso.dir.y * data->perso.speed);
	new_y = (data->perso.pos.y - (data->perso.dir.x * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)data->perso.pos.y] == '0')
        data->perso.pos.x = new_x;
    if (data->map[(int)data->perso.pos.x][(int)new_y] == '0')
        data->perso.pos.y = new_y;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x) - (data->perso.dir.y * data->perso.speed);
	new_y = (data->perso.pos.y + (data->perso.dir.x * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)data->perso.pos.y] == '0')
        data->perso.pos.x = new_x;
    if (data->map[(int)data->perso.pos.x][(int)new_y] == '0')
        data->perso.pos.y = new_y;
}

void	turn_left(t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_plan_x;
	double	new_plan_y;

	new_x = data->perso.dir.x * cos(data->perso.rot) +
		data->perso.dir.y * sin(data->perso.rot);
	new_y = data->perso.dir.y * cos(data->perso.rot) -
		data->perso.dir.x * sin(data->perso.rot);
	new_plan_x = data->perso.planx * cos(data->perso.rot) +
		data->perso.plany * sin(data->perso.rot);
	new_plan_y = data->perso.plany * cos(data->perso.rot) -
		data->perso.planx * sin(data->perso.rot);
	printf("DIR X %f DIR Y %f\n", data->perso.dir.x, data->perso.dir.y);
	printf("new_x : %f , new_y : %f\n", new_x, new_y);
    data->perso.dir.x = new_x;
    data->perso.dir.y = new_y;
    data->perso.planx = new_plan_x;
    data->perso.plany = new_plan_y;
}

void	turn_right(t_data *data)
{
	double	new_x;
	double	new_y;
	double	new_plan_x;
	double	new_plan_y;

	new_x = data->perso.dir.x * cos(data->perso.rot) -
		data->perso.dir.y * sin(data->perso.rot);
	new_y = data->perso.dir.y * cos(data->perso.rot) +
		data->perso.dir.x * sin(data->perso.rot);
	new_plan_x = data->perso.planx * cos(data->perso.rot) -
		data->perso.plany * sin(data->perso.rot);
	new_plan_y = data->perso.plany * cos(data->perso.rot) +
		data->perso.planx * sin(data->perso.rot);
	printf("DIR X %f DIR Y %f\n", data->perso.dir.x, data->perso.dir.y);
	printf("new_x : %f , new_y : %f\n", new_x, new_y);
    data->perso.dir.x = new_x;
    data->perso.dir.y = new_y;
    data->perso.planx = new_plan_x;
    data->perso.plany = new_plan_y;
}

int			key(int key, t_data *data)
{
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
	return (0);
}

void	init_ray(t_data *data, int x)
{
	data->ray.start = 0;
	data->ray.end = 0;
	data->ray.camera = (2 * x / (double)WIDTH) - 1;
	data->ray.dirx = data->perso.dir.x + data->perso.planx * data->ray.camera;
	data->ray.diry = data->perso.dir.y + data->perso.plany * data->ray.camera;
	data->cast.mapx = (int)data->perso.pos.x;
	data->cast.mapy = (int)data->perso.pos.y;
	data->cast.sidedistx = 0;
	data->cast.sidedisty = 0;
	data->cast.deltax = sqrt(1 + ((data->ray.diry * data->ray.diry) /
			(data->ray.dirx * data->ray.dirx)));
	data->cast.deltay = sqrt(1 + ((data->ray.dirx * data->ray.dirx) /
		(data->ray.diry * data->ray.diry)));
	data->cast.stepx = 0;
	data->cast.stepy = 0;
	data->cast.hit = 0;
	data->cast.side = 0;
	data->cast.walldist = 0;
}

void	raycasting(t_data *data, int x)
{
	raycast_value(data, x);
	while (data->cast.hit == 0)
	{
		if (data->cast.sidedistx < data->cast.sidedisty)
		{
			data->cast.sidedistx += data->cast.deltax;
			data->cast.mapx += data->cast.stepx;
			data->cast.side = 0;
		}
		else
		{
			data->cast.sidedisty += data->cast.deltay;
			data->cast.mapy += data->cast.stepy;
			data->cast.side = 1;
		}
		if (data->map[data->cast.mapx][data->cast.mapy] > '0')
			data->cast.hit = 1;
	}
	wall_dir(data);
}

void	raycast_value(t_data *data, int x)
{
	init_ray(data, x);
	if (data->ray.dirx < 0)
	{
		data->cast.stepx = -1;
		data->cast.sidedistx = (
				data->perso.pos.x - data->cast.mapx) * data->cast.deltax;
	}
	else
	{
		data->cast.stepx = 1;
		data->cast.sidedistx = (
				data->cast.mapx + 1.0 - data->perso.pos.x) * data->cast.deltax;
	}
	if (data->ray.diry < 0)
	{
		data->cast.stepy = -1;
		data->cast.sidedisty = (
				data->perso.pos.y - data->cast.mapy) * data->cast.deltay;
	}
	else
	{
		data->cast.stepy = 1;
		data->cast.sidedisty = (
				data->cast.mapy + 1.0 - data->perso.pos.y) * data->cast.deltay;
	}
}

void	wall_dir(t_data *data)
{
	int	heightline;

	if (data->cast.side == 0)
		data->cast.walldist = ABS((data->cast.mapx - data->perso.pos.x + (
							1 - data->cast.stepx)/2) / data->ray.dirx);
	else
		data->cast.walldist = ABS((data->cast.mapy - data->perso.pos.y + (
							1 - data->cast.stepy)/2) / data->ray.diry);
	heightline = HEIGHT / data->cast.walldist;
	data->ray.start = (int)(-(heightline / 2) + HEIGHT / 2);
	data->ray.end = (int)((heightline / 2) + HEIGHT / 2);
	if (data->ray.start < 0)
		data->ray.start = 0;
	if (data->ray.end >= HEIGHT)
		data->ray.end = HEIGHT - 1;
}

int     ft_move(t_data *data)
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
	crt_img(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
    return (0);
}

void	ft_init(t_data *data)
{
	data->perso.pos.x = 0;
	data->perso.pos.y = 0;
	data->perso.dir.x = 1;
	data->perso.dir.y = 0;
	data->perso.speed = 0.036;
	data->perso.rot = 2 * M_PI / 180;
	data->perso.plane = 70 / WIDTH;
	data->event.forward = 0;
	data->event.backward = 0;
	data->event.left = 0;
	data->event.right = 0;
	data->event.l_arrow = 0;
	data->event.r_arrow = 0;
	data->perso.planx = 0;
	data->perso.plany = 0.666;
	ft_init_map(data);
}

int		main()
{
	t_data	data;

	ft_init(&data);
	data.mlx.ptr = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.ptr, WIDTH, HEIGHT, "Cube3d");
	data.img.ptr = mlx_new_image(data.mlx.ptr, WIDTH, HEIGHT);
	data.img.buffer = (int*)mlx_get_data_addr(data.img.ptr, &data.img.bpp,
										&data.img.size, &data.img.endian);
	mlx_do_key_autorepeatoff(data.mlx.ptr);
	mlx_hook(data.mlx.win, KEYDOWN, 0, key, &data);
	mlx_hook(data.mlx.win, KEYUP, 0, key, &data);
	mlx_hook(data.mlx.win, QUIT, 0, exit_properly, &data);
	mlx_loop_hook(data.mlx.ptr, ft_move, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
