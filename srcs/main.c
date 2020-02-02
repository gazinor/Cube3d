/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/02 19:18:57 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

static int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (*(str + i))
		++i;
	return (i);
}

int		ft_size(int n)
{
	int		size;

	size = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static	char	*ft_recur(char *str, int n, int i)
{
	if (n < 0)
	{
		n = n * -1;
		str[ft_size(n)] = '-';
	}
	if (n >= 10)
	{
		ft_recur(str, n / 10, i + 1);
		ft_recur(str, n % 10, i);
	}
	else
		str[i] = n + 48;
	return (str);
}

static	void	ft_strrev(char *str)
{
	int	len;
	int	i;
	int	tmp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
		i++;
	}
}

char			*ft_itoa(int n)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * (ft_size(n) + 1))))
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = ft_recur(str, n, 0);
	str[ft_size(n)] = '\0';
	ft_strrev(str);
	return (str);
}

void	free_img(t_data *data, void *ptr)
{
	if (ptr)
		mlx_destroy_image(data->mlx.ptr, ptr);
}

void	clean_images(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_PORTAL_IMG)
		free_img(data, data->portal[i].ptr);
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
	if (error_msg)
	{
		while (error_msg[i])
			++i;
		write(2, error_msg, i);
	}
	if (error == TRUE)
	{
		write(2, "\e[31mErreur\n", 12);
		clean_images(data);
		exit(1);
	}
	clean_images(data);
	write(1, "\e[32mCub3D s'est correctement eteint.\n\e[0m", 43);
	exit(0);
}

void	print_life(t_data *data)
{
	int		x;
	int		y;
	int		debut_x;
	int		debut_y;

	debut_x = WIDTH * 5 / 8;
	debut_y = HEIGHT / 16;
	x = -1;
	while(++x < WIDTH)
	{
		y = -1;
		while(++y < HEIGHT)
			if (x > debut_x + 7  && x < debut_x + WIDTH * 2 / 8 - 7 &&
				y > debut_y + 7 && y < debut_y + HEIGHT / 32 - 7)
				data->img.buffer[x + (y * data->img.width)] = 0xFF0000;
			else if (x > debut_x  && x < debut_x + WIDTH * 2 / 8 &&
				y > debut_y && y < debut_y + HEIGHT / 32)
				data->img.buffer[x + (y * data->img.width)] = 0x0;
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
} 


char	*serialized(t_data *data)
{
	char	*str = NULL;
	char	*tmp;

	str = ft_strdup("echo \"");	
	tmp = ft_strjoin(str, ft_itoa((int)data->perso.pos.x));
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, ";");
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, ft_itoa((int)((data->perso.pos.x - (int)data->perso.pos.x) * 100)));
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, ";");
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, ft_itoa((int)data->perso.pos.y));
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, ";");
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, ft_itoa((int)((data->perso.pos.y - (int)data->perso.pos.y) * 100)));
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, "\" | nc e1r12p12 13000");
//	tmp = ft_strjoin(str, "\" | nc localhost 13000");
	free(str);
	str = tmp;
	return (str);
}

int		key_on(int key, t_data *data)
{
	if (data->event.menu == 1 || data->event.option == 1)
		return (0);
	if (key == DOOR && data->map[(int)data->perso.pos.x]
			[(int)data->perso.pos.y] != '4' && data->option.status == 1)
	{
		system("echo \"open door\" | nc e1r12p12 13000");
//		system("echo \"open door\" | nc localhost 13000");
		data->event.door ^= 1;
		data->event.remote ^= 1;
	}
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

long	dark(long color, double alpha)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (alpha < 0)
		return (color);
	if (alpha > 1)
		return (color);
	t = ((color >> 24) & 0xff) * alpha;
	r = ((color >> 16) & 0xff) * alpha;
	g = ((color >> 8) & 0xff) * alpha;
	b = (color & 0xff) * alpha;
	return ((t << 24) + (r << 16) + (g << 8) + b);
}

void	put_image_to_window(t_data *data)
{
	int		i;
	i = -1;
	data->old_time = data->time.tv_usec + data->time.tv_sec * 1000000;
	gettimeofday(&data->time, NULL);
	data->anim += (data->time.tv_usec + data->time.tv_sec * 1000000) - data->old_time;
	data->option.status == 1 ? print_life(data) : 1;
	while (++i < HEIGHT * WIDTH)
		data->img.buffer[i] = dark(data->img.buffer[i],
		data->anim / 1500000.0);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	if (data->event.remote == 1)
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
	char 	*ret = NULL;

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
	pthread_mutex_lock(&data->mutex_player);
	if (data->player)
	{
		print_obj(data, data->player);
		free_obj(data->player);
		data->player = NULL;
	}	
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
		data->portal_index = (data->portal_index + 1) % NB_PORTAL_IMG;
		print_portal(data, data->portal_lst);
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

void    load_portal(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_PORTAL_IMG)
		load_image(data, &data->portal[i], 1000, 1000);
}

t_bool	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (FALSE);
	if (s2[i] != '\0')
		return (FALSE);
	return (TRUE);
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	ft_test(t_data *data, char buf[4097])
{
	static int	x = 0;
	static int	x_ = 0;
	static int	y = 0;
	static int	y_ = 0;
	int			i;

	i = 0;
	while (!ft_isdigit(buf[i]))
		++i;
	x = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	x_ = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	y = atoi(buf + i);
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	y_ = atoi(buf + i);
	pthread_mutex_lock(&data->mutex_player);
	create_obj(data, &data->player, 0);
	data->player->sac.ray.mapx = x + x_ / 100. - 0.5;
	data->player->sac.ray.mapy = y + y_ / 100. - 0.5;
	data->player->sac.ray.walldist = sqrt((data->perso.pos.x - (x + x_ / 100.)) *
(data->perso.pos.x - (x + x_ / 100.)) + (data->perso.pos.x - (y + y_ / 100.)) * (data->perso.pos.x - (y + y_ / 100.)));
	pthread_mutex_unlock(&data->mutex_player);
}

void    *t_loop(void *arg)
{
	int     fd = open("/dev/fd/0", O_RDONLY | O_NONBLOCK);
	char    buf[4097];
	int     ret;

	t_data *data = (t_data *)arg;
	data->launch = FALSE;
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		buf[ret] = 0;
		if (!strncmp(buf, "open door", 9))
			data->event.door ^= 1;
		else
			if (data->launch == TRUE)
				ft_test(data, buf);
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_data data;
	pthread_t	thread;

	if (ac != 3 && ac != 2)
	{
		write(2, "\e[31mErreur\n", 12);
		write(2, "Mauvais nombre d'arguments.\n", 28);
		exit(0);
	}
	pthread_mutex_init(&data.mutex_player, NULL);
	pthread_create(&thread, NULL, t_loop, &data);
	ft_init(&data);
	crt_window(&data);
	parsing(av[1], &data);
	load_background(&data);
	load_dir_textures(&data);
	load_objs(&data);
	load_portal(&data);
	load_menu(&data);
	load_option(&data);
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "-save") == TRUE ||
				ft_strcmp(av[2], "--save") == TRUE)
		{
			data.screen = 1;
			init_normale(&data);
			loop(&data);
		}
		else
			exit_properly(&data, 1, "Unknown argument.\n");
	}
	system("afplay sounds/bgm.mp3 &");
	data.event.music = 1;
	menu(&data);
	return (0);
}
