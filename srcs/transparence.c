/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:57:14 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 21:52:32 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		transparance(int p1, int p2)
{
	double	transparance;
	int		r;
	int		g;
	int		b;

	transparance = 1 - ((((p1 & 0xFF000000) >> 24) -
			((p2 & 0xFF000000) >> 24)) / 255.);
	r = ((transparance * ((p1 & 0xFF0000) >> 16)) +
			((p2 & 0xFF0000) >> 16)) / 2;
	g = ((transparance * ((p1 & 0xFF00) >> 8)) + ((p2 & 0xFF00) >> 8)) / 2;
	b = ((transparance * (p1 & 0xFF)) + (p2 & 0xFF)) / 2;
	return ((r << 16) + (g << 8) + b);
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
