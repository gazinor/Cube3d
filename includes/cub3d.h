/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/30 00:17:38 by glaurent         ###   ########.fr       */
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
# define U_ARROW 126
# define D_ARROW 125
# define ENTER 36
# define DOOR 14
# define RUN 257
# define RESPAWN 15
# define TAB 48
# define SCREENSHOT 105
# define MENU 35
# define NB_PORTAL_IMG 83

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <signal.h>
# include <fcntl.h>
#include <pthread.h>

extern char     *g_portal[NB_PORTAL_IMG];

typedef enum	e_bool
{
	FALSE = 0,
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
	char		*filename;
	t_bool		check;
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
	t_bool		menu;
	t_bool		screenshot;
	t_bool		option;
	t_bool		music;
}				t_event;

typedef struct	s_menu
{
	int			i;
	t_bool		button[3];
}				t_menu;

typedef struct	s_option
{
	int			i;
	t_bool		status;
	t_bool		button[2];
}				t_option;

typedef	struct	s_mod
{
	t_bool		nbr[3];
	int			i;
	double		light;
}				t_mod;

typedef	struct	s_ray
{
	double			mapx;
	double			mapy;
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

typedef struct	s_sac
{
	t_ray 		ray;
	int			column;
}				t_sac;

typedef	struct	s_sprite
{
	t_sac		sac;
	struct s_sprite	*next;
}				t_sprite;

typedef struct	s_parse
{
	t_img		ntext;
	t_img		wtext;
	t_img		stext;
	t_img		etext;
	t_img		sprite_text;
	long		f_color;
	long		c_color;
	char		**map;
	int			sizeline;
	int			nb_line;
	int			i;
	t_pos		pos;
	t_pos		dir;
	double		planx;
	double		plany;
	t_bool		check_r;
	t_bool		check_s;
	t_bool		check_f;
	t_bool		check_c;
	t_bool		check_map;
}				t_parse;

typedef struct	s_calc
{
	double		calcx;
	double		calcy;
	double		ratio;
	double		lum;
	double		offset;
}				t_calc;

typedef struct	s_bonus
{
	char		**map;
	t_pos		dir;
	t_pos		pos;
	double		planx;
	double		plany;
}				t_bonus;

typedef struct  s_portal
{
	t_ray			ray;
    struct s_portal *next;
}               t_portal;

typedef	struct	s_data
{
	t_perso			perso;
	t_img			img;
	t_mlx			mlx;
	t_event			event;
	t_ray			ray;
	t_img			ciel;
	t_img			ciel_etoile;
	t_img			sol;
	t_img			ntext;
	t_img			stext;
	t_img			etext;
	t_img			wtext;
	t_img			odoor;
	t_img			cdoor;
	t_img			remote;
	t_img			i_menu;
	t_img			play_s_contour;
	t_img			play_uns_contour;
	t_img			option_s_contour;
	t_img			option_uns_contour;
	t_img			quit_s_contour;
	t_img			quit_uns_contour;
	t_img			on_button;
	t_img			off_button;
	t_img			mode_bonus;
	t_img			retour_s;
	t_img			retour_uns;
	t_img			sprite;
	t_img			portal[NB_PORTAL_IMG];
	t_portal		*portal_lst;
	t_mod			mod;
	t_menu			menu;
	t_option		option;
	t_parse			parse;
	t_calc			calc;
	pid_t			music;
	char			**map;
	t_pos			map_mid;
	t_sprite		*door;
	t_sprite		*obj;
	t_sprite		*player;
	int				numSprites;
	double			ZBuffer[WIDTH];
	t_bonus			bonus;
	int				w;
	int				h;
    int				portal_index;
	t_bool			screen;
	t_bool			launch;
	pthread_mutex_t	mutex_player;
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
void			free_portal(t_portal *obj);
long			dark(int color, double walldist, t_data *data);
void			print_door(t_data *data, t_sprite *obj);
long			trans(int color, t_data *data, int i, int limit);
void			menu(t_data *data);
void			load_menu(t_data *data);
int				exit_properly(t_data *data, t_bool error, char *error_msg);
void			loop(t_data *data);
void			print_obj(t_data *data, t_sprite *obj);
void			*create_obj(t_data *data, t_sprite **obj, int column);
void			screenshot(t_data *data);
long			ground_dark(long color, double dist);
void			load_image(t_data *data, t_img *img, int width, int height);
void			load_option(t_data *data);
void			option(t_data *data);
int				get_next_line(int fd, char **line);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_substr(const char *s, unsigned int start, size_t len);
void			parsing(char *parse, t_data *data);
double			my_abs(double value);
void			print_portal(t_data *data, t_portal *portal);
void			*create_portal(t_data *data, t_portal **portal_lst);
t_bool			check_portal(t_data *data, double new_x, double new_y);
t_pos			set_dir_portal(char c);
t_bool			ft_strcmp(char *s1, char *s2);
void			init_normale(t_data *data);

#endif
