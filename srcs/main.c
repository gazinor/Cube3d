/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:57:37 by glaurent          #+#    #+#             */
/*   Updated: 2020/02/12 09:51:47 by glaurent         ###   ########.fr       */
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
//	write(error == TRUE ? 2 : 1, "\n", 1);
	if (data->event.music == 1)
		system("killall afplay");
	if (error == TRUE)
	{
		write(2, "\n\e[31mErreur\n", 13);
		if (error_msg)
		{
			while (error_msg[i])
				++i;
			write(2, error_msg, i);
		}
		clean_images(data);
		exit(1);
	}
	clean_images(data);
	write(1, "\n\e[32mCub3D s'est correctement eteint.\n\e[0m", 44);
	exit(0);
}

void	color_screen(t_data *data, long color)
{
	int		x;
	int		y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			data->img.buffer[x + (y * data->img.width)] = color;
	}
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

t_bool	tolerance(long color, long tolerance)
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	t = (color >> 24);
	r = (color >> 16);
	g = (color >> 8);
	b = color;
	if (t < tolerance && r < tolerance && g < tolerance && b < tolerance)
		return (TRUE);
	return (FALSE);

}

void	you_died(t_data *data)
{
	int		i;
	int		color;

	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		if (i > HEIGHT / 4 * WIDTH && i < HEIGHT * 3 / 4 * WIDTH)
		{
			if (tolerance((color = data->you_died[(int)data->you_died_index].buffer[i -
							(HEIGHT / 4 * WIDTH)]), 0x99) == TRUE)
				data->img.buffer[i] = dark(data->img.buffer[i],
						(6000000.0 - data->anim) / 6000000.0);
			else if (i > HEIGHT / 4 * WIDTH && i < HEIGHT * 3 / 4 * WIDTH)
				data->img.buffer[i] = dark(color, (data->anim % 2) == 0 &&
						data->anim < 2000000.0 ? (2000000.0 - data->anim / 2000000.0) :
						(data->anim) / 6000000.0);
		}
		else
			data->img.buffer[i] = dark(data->img.buffer[i],
					(6000000.0 - data->anim) / 6000000.0);
	}
}

void	print_life(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while(++x < WIDTH)
	{
		y = -1;
		while(++y < HEIGHT)
			if (x > data->life.debut_x + 7  && x < data->life.debut_x +
					data->life.max_life - data->life.hurt - 7 &&
					y > data->life.debut_y + 7 && y < data->life.debut_y + data->life.fin_y - 7)
				data->img.buffer[x + (y * data->img.width)] = 0xFF0000;
			else if (x > data->life.debut_x  && x < data->life.debut_x + data->life.max_life &&
					y > data->life.debut_y && y < data->life.debut_y + data->life.fin_y)
				data->img.buffer[x + (y * data->img.width)] = 0x330000;
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
	else if (key == SLASH)
	{
		data->sword_index = 0;
		if (data->player && (data->player->sac.ray.mapx - data->perso.pos.x) *
				data->perso.dir.x < 1 && (data->player->sac.ray.mapy - data->perso.pos.y) *
				data->perso.dir.y < 1)
			data->event.hit ^= 1;
	}
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
	tmp = ft_strjoin(str, ";");
	free(str);
	str = tmp;
	tmp = ft_strjoin(str, data->event.hit == TRUE ? ft_itoa((int)data->life.hit) : 0);
	free(str);
	str = tmp;
	//	tmp = ft_strjoin(str, "\" | nc e1r2p19 13000");
	tmp = ft_strjoin(str, "\" | nc localhost 13000");
	free(str);
	str = tmp;
	data->event.hit = FALSE;
	return (str);
}

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


void	print_sword(t_data *data, int index)
{
	int		x;
	int		y;
	int		color;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			if (x > WIDTH / 2)
			{
				color = data->sword[index].buffer[
					x - WIDTH / 2 + (y * data->sword[index].width)];
				if ((color & 0xDC6400) != 0)
					data->img.buffer[x + (y * data->img.width)] = color;
			}
	}
}

void	print_screamer(t_data *data, int index)
{
	int		x;
	int		y;
	int		color;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			color = data->screamer[index].buffer[
			x + (y * data->screamer[index].width)];
			data->img.buffer[x + (y * data->img.width)] = color;
		}
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
	pthread_mutex_unlock(&data->mutex_player);
	if (data->monster_lst)
	{
		print_obj(data, data->monster_lst);
//		free_obj(data->monster_lst);
//		data->monster_lst = NULL;
	}
	if (data->map[(int)data->perso.pos.x][(int)data->perso.pos.y] == 'x')
		data->life.hurt += 0.01 * data->life.max_life;
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
	data->download_percent += 0.31274;
}

void	load_background(t_data *data)
{
	load_image(data, &data->ciel, 9 * HEIGHT, HEIGHT / 2);
	load_image(data, &data->sol, 1000, 1000);
	load_image(data, &data->ciel_etoile, 9 * HEIGHT, HEIGHT / 2);
	load_image(data, &data->plafond, 1000, 1000);
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
	load_image(data, &data->spikes, 1000, 1000);
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

void    load_sword(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_SWORD_IMG)
		load_image(data, &data->sword[i], WIDTH / 2, HEIGHT);
}

void    load_you_died(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_YOU_DIED_IMG)
		load_image(data, &data->you_died[i], WIDTH, HEIGHT / 2);
}

void    load_player2(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_PLAYER2_IMG)
		load_image(data, &data->player2[i], 1000, 1000);
}

void    load_door(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_DOOR_IMG)
		load_image(data, &data->gif_door[i], 1000, 1000);
}

void    load_screamer(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_SCREAMER_IMG)
		load_image(data, &data->screamer[i], WIDTH, HEIGHT);
}

void    load_monster(t_data *data)
{
	int     i;

	i = -1;
	while (++i < NB_MONSTER_IMG)
		load_image(data, &data->monster[i], 1000, 1000);
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
	while (ft_isdigit(buf[i]))
		++i;
	++i;
	i = atoi(buf + i);
	if (i > 0)
	{
		data->life.hurt += i;
		data->life.blood = 5;
	}
	pthread_mutex_lock(&data->mutex_player);
	create_obj(data, &data->player, data->player2[(int)data->player2_index], 0);
	data->player2_index = (int)(data->player2_index + 1) % NB_PLAYER2_IMG;
	data->player->sac.ray.mapx = x + x_ / 100. - 0.5;
	data->player->sac.ray.mapy = y + y_ / 100. - 0.5;
	data->player->sac.ray.walldist = sqrt((data->perso.pos.x - (x + x_ / 100.))
			* (data->perso.pos.x - (x + x_ / 100.)) + (data->perso.pos.x - (y + y_ / 100.))
			* (data->perso.pos.x - (y + y_ / 100.)));
	pthread_mutex_unlock(&data->mutex_player);
}

void    *t_loop(void *arg)
{
	int     fd = open("/dev/fd/0", O_RDONLY | O_NONBLOCK);
	char    buf[4097];
	int     ret;
	t_data	*data;

	data = (t_data *)arg;
	data->launch = FALSE;
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		buf[ret] = 0;
		if (!strncmp(buf, "open door", 9))
			data->door_index = 0;
		else
			if (data->launch == TRUE)
				ft_test(data, buf);
	}
	return (NULL);
}

void	*draw_downloading(void *arg)
{
	int		i;
	int		j;
	t_data	*data;

	data = (t_data *)arg;
	write(1, "\n\n\n\n", 4);
	i = 0;
	while(i < 81)
	{
		j = -1;
		write(1, "\e[1;4;38;5;123m", 15);
		write(1, ft_itoa(i * 1.25), 1 + ((i * 1.25 < 100) ? 1 : 2));
		write(1, "%\e[0m \e[48;5;52m", 16);
		while (++j < i)
			write(1, "\e[0;107m ", 10);
		write(1, "\e[48;5;52m", 11);
		while (++j < 81)
			write(1, " ", 1);
		write(1, "\e[0m", 5);
		fflush(stdout);
		usleep(30000);
		write(1, "\r", 1);
		i = (int)data->download_percent;
	}
	return (NULL);
}

void	*use_monsters(void *arg)
{
	t_data		*data;
	double		x;
	double		y;

	data = (t_data *)arg;
	x = 2.5;
	y = 2.5;
	while (1)
		if (data->launch == TRUE)
		{
			pthread_mutex_lock(&data->mutex_player);
			printf("%f | %f\n", x, y);
			if (!data->monster_lst)
				create_obj(data, &data->monster_lst, data->monster[(int)data->monster_index % NB_MONSTER_IMG], 0);
			data->monster_index += 0.1;
			data->monster_lst->sac.img = data->monster[(int)data->monster_index % NB_MONSTER_IMG];
			data->monster_lst->sac.ray.mapx = x;
			data->monster_lst->sac.ray.mapy = y;
			data->monster_lst->sac.ray.walldist = sqrt((data->perso.pos.x - x)
				* (data->perso.pos.x - x) + (data->perso.pos.x - y)
				* (data->perso.pos.x - y));
			x = (data->perso.pos.x - data->monster_lst->sac.ray.mapx) /
			(double)data->monster_lst->sac.ray.walldist;
			y = (data->perso.pos.y - data->monster_lst->sac.ray.mapy) /
			(double)data->monster_lst->sac.ray.walldist;
			pthread_mutex_unlock(&data->mutex_player);
			usleep(10000);
		}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_data		data;
	pthread_t	thread;
	pthread_t	download;
	pthread_t	monster;

	if (ac != 3 && ac != 2)
	{
		write(2, "\e[31mErreur\n", 12);
		write(2, "Mauvais nombre d'arguments.\n", 28);
		exit(0);
	}
	pthread_mutex_init(&data.mutex_player, NULL);
	pthread_create(&download, NULL, draw_downloading, &data);
	pthread_create(&thread, NULL, t_loop, &data);
	pthread_create(&monster, NULL, use_monsters, &data);
	ft_init(&data);
	crt_window(&data);
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
