/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 03:33:11 by glaurent          #+#    #+#             */
/*   Updated: 2019/12/03 04:44:31 by glaurent         ###   ########.fr       */
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

# include <stdlib.h>
# include <stdio.h>

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef	struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef	struct	s_img
{
	void	*ptr;
	int		*buffer;
	int		bpp;
	int		size;
	int		endian;
}				t_img;

typedef	struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef	struct	s_perso
{
	t_pos	pos;
	t_pos	dir;
	double	speed;
	double	rot;
	double	plane;
}				t_perso;

typedef	struct	s_event
{
	t_bool	forward;
	t_bool	backward;
	t_bool	left;
	t_bool	right;
	t_bool	l_arrow;
	t_bool	r_arrow;
}				t_event;

typedef	struct	s_data
{
	t_perso		perso;
	t_img		img;
	t_mlx		mlx;
	t_event		event;
	char		**map;
	int			start;
	int			end;
}				t_data;

void	*ft_init_map(t_data *data);
void	ft_fill_map(t_data *data);

#endif
