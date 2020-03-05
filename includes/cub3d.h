/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 01:32:09 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 1200
# define HEIGHT 1000
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
# define SLASH 126
# define NB_PORTAL_IMG 83
# define NB_SWORD_IMG 37
# define NB_YOU_DIED_IMG 75
# define NB_PLAYER2_IMG 4
# define NB_DOOR_IMG 11
# define NB_SCREAMER_IMG 11
# define NB_MONSTER_IMG 8
# define NB_TP 56

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <signal.h>
# include <fcntl.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

extern char     *g_portal[NB_PORTAL_IMG];
extern char     *g_sword[NB_SWORD_IMG];
extern char     *g_you_died[NB_YOU_DIED_IMG];
extern char     *g_player2[NB_PLAYER2_IMG];
extern char     *g_door[NB_DOOR_IMG];
extern char     *g_screamer[NB_SCREAMER_IMG];
extern char     *g_monster[NB_MONSTER_IMG];
extern char     *g_tp[NB_TP];

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
	t_bool		remote;
	t_bool		run;
	t_bool		respawn;
	t_bool		menu;
	t_bool		screenshot;
	t_bool		option;
	t_bool		music;
	t_bool		hit[3];
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
	double		mapx;
	double		mapy;
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
	double		wallx;
	double		f_xwall;
	double		f_ywall;
	double		cur_dist[HEIGHT];
	double		weight;
	double		cur_floorx;
	double		cur_floory;
	int			f_texx;
	int			f_texy;
}				t_ray;

typedef struct	s_sac
{
	t_ray 		ray;
	int			column;
	t_img		img;
	int			down;
	int			trap;
	double		index;
	int			id;
}				t_sac;

typedef struct	s_norme_door
{
	int			i;
	int			j;
	int			true_start;
	int			t_e;
	int			color;
	double		calc1;
	double		calc2;
	double		ratio;
	double		luminosity;	
}				t_norme_door;

typedef struct	s_norme_obj
{
	int			stripe;
	int			y;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	double		luminosity;
	int			texx;
	int			d;
	int			texy;
	int			color;
}				t_norme_obj;

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

typedef struct	s_life
{
	int			debut_x;
	int			debut_y;
	int			fin_y;
	int			max_life;
	int			hurt;
	int			life;
	int			hit;
	int			blood;
	t_bool		alive;
}				t_life;

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
	t_img			plafond;
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
	t_img			spikes;
	t_img			portal[NB_PORTAL_IMG];
	t_img			sword[NB_SWORD_IMG];
	t_img			you_died[NB_YOU_DIED_IMG];
	t_img			player2[NB_PLAYER2_IMG];
	t_img			gif_door[NB_DOOR_IMG];
	t_img			screamer[NB_SCREAMER_IMG];
	t_img			monster[NB_MONSTER_IMG];
	t_img			tp[NB_TP];
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
	t_sprite		*monster_lst;
	t_sprite		*tp_lst;
	int				numSprites;
	double			zbuffer[WIDTH];
	t_bonus			bonus;
	int				w;
	int				h;
	double			portal_index;
	double			sword_index;
	double			you_died_index;
	double			player2_index;
	double			door_index;
	double			screamer_index;
	double			monster_index;
	double			tp_index;
	unsigned long	anim;
	t_bool			screen;
	t_bool			launch;
	double			download_percent;
	struct timeval	time;
	unsigned long	old_time;
	t_life			life;
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
void			print_door(t_data *data, t_sprite *obj, t_img rend);
long			trans(int color, t_data *data, int i, int limit);
void			menu(t_data *data);
void			load_menu(t_data *data);
int				exit_properly(t_data *data, t_bool error, char *error_msg);
void			loop(t_data *data);
void			print_obj(t_data *data, t_sprite *obj);
void			*create_obj(t_data *data, t_sprite **obj, t_img img, int down);
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
void			print_portal(t_data *data, t_portal *portal, int index);
void			*create_portal(t_data *data, t_portal **portal_lst);
t_bool			check_portal(t_data *data, double new_x, double new_y);
t_pos			set_dir_portal(char c);
t_bool			ft_strcmp(char *s1, char *s2);
void			init_normale(t_data *data);
int				transparance(int p1, int p2);
void			ft_init_player(t_data *data);
void			floorcasting(t_data *data, int y);
void			draw_ground(t_data *data, int y, int x, double ratio);
void			draw_sky(t_data *data, int y, int x, double ratio);
void			init_bonus(t_data *data);
void			init_normale(t_data *data);
int				ft_strlen(char *str);
void			load_menu(t_data *data);
void			put_img_to_win_coord(t_data *data, void *ptr, int x, int y);
char			**ft_tabdup(char **str);
void			init_calc(t_data *data, t_img texture);
long			ground_dark(long color, double dist);
t_img			get_texture(t_data *data);
void			init_gif_ptr(t_data *data, int i);
void			init_gif_filename(t_data *data, int i);
void			init_filenames(t_data *data);
void			init_img(t_data *data);
int				ft_atoi_parse(char *str, int *res, t_data *data);
void			check_pixel(t_data *data, int r, int g, int b);
t_img			*get_img(char *line, t_data *data);
void			check_sky(char *line, t_data *data);
void			check_floor(char *line, t_data *data);
void			check_file_extension(t_data *data, char *path);
void			init_parse_map(t_data *data, char *path);
void			check_all_cases(char *line, t_data *data);
void			malloc_map(t_data *data);
void			check_res(char *line, t_data *data);
void			set_parse_dir(t_data *data, char c);
int				ft_strlen_map(t_data *data, char *str, int token);
void			check_parse_map(t_data *data);
void			check_tex(char *line, t_data *data);
void			fill_parse_map(char *line, t_data *data);
int				in_parse_map(char *line, t_data *data, int i, int j);
void			parsing(char *path, t_data *data);
double			my_abs(double value);
t_norme_door	set_door_vars(t_data *data, t_sprite *obj, t_img rend);
void			print_door(t_data *data, t_sprite *obj, t_img rend);
void			*create_door(t_data *data, t_sprite **obj, int column);
void			sort_list(t_sprite **obj);
void			free_portal(t_portal *obj);
char			*ft_itoa(int n);
void			color_screen(t_data *data, long color);
void			you_died(t_data *data);
void			print_life(t_data *data);
void			print_sword(t_data *data, int index);
void			print_screamer(t_data *data, int index);
long			dark(long color, double alpha);
t_bool			tolerance(long color, long tolerance);
void			free_img(t_data *data, void *ptr);
void			clean_images(t_data *data);
int				exit_properly(t_data *data, t_bool error, char *error_msg);
int				key_on(int key, t_data *data);
int				key_off(int key, t_data *data);
int				ft_move2(t_data *data);
int				ft_move(t_data *data);
void			intern_key(int key, t_data *data);
void			put_image_to_window(t_data *data);
void			check_door(t_data *data);
void			check_mod(t_data *data);
void			do_in_order(t_data *data);
void			crt_window(t_data *data);
void			load_image(t_data *data, t_img *img, int width, int height);
void			load_background(t_data *data);
void			load_dir_textures(t_data *data);
void			load_objs(t_data *data);
void		    load_portal(t_data *data);
void		    load_sword(t_data *data);
void		    load_you_died(t_data *data);
void		    load_player2(t_data *data);
void		    load_door(t_data *data);
void		    load_screamer(t_data *data);
void		    load_monster(t_data *data);
void		    load_tp(t_data *data);
void			ft_player2(t_data *data, char buf[4097]);
void		    *t_loop(void *arg);
void			*draw_downloading(void *arg);
void			*do_tp(void *arg);
void			*use_monsters(void *arg);
int				ft_isdigit(char c);
char			*join_n_free(char *s1, char *s2);
char			*serialized(t_data *data);

#endif
