/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/04 19:48:07 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIDTH 800
# define HEIGHT 600
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
# define ABS(Value) (Value < 0) ? -Value : Value

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

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
}				t_img;

typedef	struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef	struct	s_perso
{
	t_pos		pos;
	t_pos		dir;
	double		planx;
	double		plany;
	double		speed;
	double		rot;
	double		plane;
}				t_perso;

typedef	struct	s_event
{
	t_bool		forward;
	t_bool		backward;
	t_bool		left;
	t_bool		right;
	t_bool		l_arrow;
	t_bool		r_arrow;
}				t_event;

typedef	struct	s_ray
{
	int			start;
	int			end;
	double		dirx;
	double		diry;
	double		camera;
}				t_ray;

typedef	struct	s_cast
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
}				t_cast;


typedef	struct	s_data
{
	t_perso		perso;
	t_img		img;
	t_mlx		mlx;
	t_event		event;
	t_ray		ray;
	t_cast		cast;
	char		**map;
}				t_data;

void	*ft_init_map(t_data *data);
void	ft_fill_map(t_data *data);
void    crt_column(t_data *data, int column);
void    *crt_img(t_data *data);
void    raycasting(t_data *data, int x);
void    wall_dir(t_data *data);
void    raycast_value(t_data *data, int x);

#endif
