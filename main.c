/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/03 22:23:56 by glaurent         ###   ########.fr       */
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
	"1111111111",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000N00001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1111111111"
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
			if (G_BUFFER[i][j] == 'N' || G_BUFFER[i][j] == 'S' ||
			G_BUFFER[i][j] == 'E' || G_BUFFER[i][j] == 'O')
			{
				data->perso.pos.x = G_BUFFER[i];
				data->perso.pos.y = G_BUFFER[i][j];
			}
			data->map[i][j] = G_BUFFER[i][j];
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
while (x < WIDTH)
	

void		*crt_img(t_data *data)
{
	int i;

	i = -1;
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
											&data->img.size, &data->img.endian);
	while (x < WIDTH)
}

void		crt_column(t_data data, int column)
{
	while (++i < start * (data->img.size / 4))
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFFFF;
	i--;
	while (++i < end * (data->img.size / 4))
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xFF0000;
	i--;
	while (++i < HEIGHT * (data->img.size / 4))
		data->img.buffer[column + (i * (data->img.size / 4))] = 0xA0AAAAAA;
}

/*void		*crt_sky(t_data *data)
{
	int				i;

	i = -1;
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT / 2);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
											&data->img.size, &data->img.endian);
	while (++i < (HEIGHT / 2) * (data->img.size / 4))
		data->img.buffer[i] = 0xFFFF;
	return (data->img.ptr);
}

void		*crt_ground(t_data *data)
{
	int				i;

	i = -1;
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT / 2);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
											&data->img.size, &data->img.endian);
	while (++i < (HEIGHT / 2) * (data->img.size / 4))
		data->img.buffer[i] = 0xA0AAAAAA;
	return (data->img.ptr);
}*/

int			key(int key, t_data *data)
{
	if (key == ESC)
		exit_properly(FALSE, NULL);
	else if (data->event.forward == FALSE && key == FORWARD)
        data->event.forward = TRUE;
    else if (data->event.backward == FALSE && key == BACKWARD)
        data->event.backward = TRUE;
    else if (data->event.right == FALSE && key == RIGHT)
        data->event.right = TRUE;
    else if (data->event.left == FALSE && key == LEFT)
        data->event.left = TRUE;
    else if (data->event.forward == TRUE && key == FORWARD)
        data->event.forward = FALSE;
    else if (data->event.backward == TRUE && key == BACKWARD)
        data->event.backward = FALSE;
    else if (data->event.right == TRUE && key == RIGHT)
        data->event.right = FALSE;
    else if (data->event.left == TRUE && key == LEFT)
        data->event.left = FALSE;
	return (0);
}

void	move_forward(t_data data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x + (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y + (data->perso.dir.y * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)new_y] == 0)
	{
        data->perso.pos.x = new_x;
        data->perso.pos.y = new_y;
	}
}

void	move_backward(t_data data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x - (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y - (data->perso.dir.y * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)new_y] == 0)
	{
        data->perso.pos.x = new_x;
        data->perso.pos.y = new_y;
	}
}

void	move_left(t_data data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x + (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y - (data->perso.dir.y * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)new_y] == 0)
	{
        data->perso.pos.x = new_x;
        data->perso.pos.y = new_y;
	}
}

void	move_right(t_data data)
{
	double	new_x;
	double	new_y;

	new_x = (data->perso.pos.x - (data->perso.dir.x * data->perso.speed));
	new_y = (data->perso.pos.y + (data->perso.dir.y * data->perso.speed));
	printf("POS X %f POS Y %f\n", data->perso.pos.x, data->perso.pos.y);
    if (data->map[(int)new_x][(int)new_y] == 0)
	{
        data->perso.pos.x = new_x;
        data->perso.pos.y = new_y;
	}
}

void	raycasting(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		
	}
}

int     ft_move(t_data *data)
{
    if (data->event.forward == TRUE)
		move_forward(data);
	if (data->event.backward == TRUE)
		move_backward(data);
    if (data->event.right == TRUE)
		move_right(data);
    if (data->event.left == TRUE)
		move_left(data);
	raycasting(data);
	mlx_put_image_to_window(data.mlx.ptr, data.mlx.win, crt_img(&data), 0, 0);
    return (0);
}

void	ft_init(t_data *data)
{
	data->perso.pos.x = 0;
	data->perso.pos.y = 0;
	data->perso.dir.x = 0;
	data->perso.dir.y = 0;
	data->perso.speed = 0.00016;
	data->perso.rot = 2 * M_PI / 180;
	data->perso.plane = 70 / WIDTH;
	data->event.forward = FALSE;
	data->event.backward = FALSE;
	data->event.left = FALSE;
	data->event.right = FALSE;
	data->event.l_arrow = FALSE;
	data->event.r_arrow = FALSE;
	ft_init_map(data);
}

int 	main()
{
	t_data	data;

	ft_init(&data);
	data.mlx.ptr = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.ptr, WIDTH, HEIGHT, "Cube3d");
//	mlx_put_image_to_window(data.mlx.ptr, data.mlx.win, crt_sky(&data), 0, 0);
//	mlx_put_image_to_window(data.mlx.ptr, data.mlx.win, crt_ground(&data), 0, HEIGHT / 2);
	mlx_do_key_autorepeatoff(data.mlx.ptr);
	mlx_hook(data.mlx.win, KEYDOWN, 0, key, &data);
	mlx_hook(data.mlx.win, KEYUP, 0, key, &data);
	mlx_hook(data.mlx.win, QUIT, 0, exit_properly, &data);
	mlx_loop_hook(data.mlx.ptr, ft_move, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
