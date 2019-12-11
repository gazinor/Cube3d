/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/11 11:33:15 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1440
# define HEIGHT 980
# define KEYUP 3
# define KEYDOWN 2
# define ESC 53
# define QUIT 17
# define LEFT 0
# define RIGHT 2
# define FORWARD 13
# define BACKWARD 1
# define L_ARROW 123
# define R_ARROW 124
# define DOOR 14
# define RUN 257
# define RESPAWN 15
# define TAB 48
# define ABS(Value) (Value < 0) ? -Value : Value

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <signal.h>

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef enum	e_mod_type
{
	NORMAL = 0,
	DARK,
	MIRROR
}				t_mod_type;

typedef	struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef	struct	s_img
{
	void		*ptr;
	int			*buffer;
	int			bpp;
	int			size;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef	struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef	struct	s_perso
{
	t_pos		pos;
	t_pos		depart;
	t_pos		dir;
	double		planx;
	double		plany;
	double		speed;
	double		rot;
}				t_perso;

typedef	struct	s_event
{
	t_bool		forward;
	t_bool		backward;
	t_bool		left;
	t_bool		right;
	t_bool		l_arrow;
	t_bool		r_arrow;
	t_bool		door;
	t_bool		run;
	t_bool		respawn;
}				t_event;

typedef	struct	s_mod
{
	t_bool		nbr[3];
	int			i;
	double		light;
}				t_mod;

typedef	struct	s_ray
{
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltax;
	double		deltay;
	double		stepx;
	double		stepy;
	double		hit;
	double		side;
	double		walldist;
	int			start;
	int			end;
	int			truestart;
	int			trueend;
	double		dirx;
	double		diry;
	double		camera;
	int			heightline;
}				t_ray;

typedef	struct	s_sprite
{
	t_ray			ray;
	int				column;
	struct s_sprite	*next;
}				t_sprite;

typedef	struct	s_data
{
	t_perso		perso;
	t_img		img;
	t_mlx		mlx;
	t_event		event;
	t_ray		ray;
	t_img		ciel;
	t_img		ciel_etoile;
	t_img		sol;
	t_img		ntext;
	t_img		stext;
	t_img		etext;
	t_img		wtext;
	t_img		tmp_ciel;
	t_img		tmp_ciel_etoile;
	t_img		tmp_sol;
	t_img		tmp_ntext;
	t_img		tmp_stext;
	t_img		tmp_etext;
	t_img		tmp_wtext;
	t_img		odoor;
	t_img		tmp_odoor;
	t_img		cdoor;
	t_img		tmp_cdoor;
	t_img		remote;
	t_img		tmp_remote;
	t_mod		mod;
	pid_t		music;
	char		**map;
	t_sprite	*door;
}				t_data;

void			*crt_img(t_data *data);
void			crt_column(t_data *data, int column);
void			raycasting(t_data *data, int x);
void			raycast_value(t_data *data, int x);
void			wall_dist(t_data *data);
void			init_ray(t_data *data, int x);
void			ft_init(t_data *data);
void			*ft_init_map(t_data *data);
void			ft_fill_map(t_data *data);
void			move_forward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			turn_left(t_data *data);
void			turn_right(t_data *data);
t_img			resize_image(t_data *data, t_img *src, int width, int height);
void			*create_door(t_data *data, t_sprite **obj, int column);
void			free_obj(t_sprite *obj);
long			dark(int color, double walldist, t_data *data);
void			print_door(t_data *data, t_sprite *obj);
long			trans(int color, t_data *data, int i, int limit);

#endif
