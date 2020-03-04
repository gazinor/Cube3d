/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:57:14 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 01:57:41 by glaurent         ###   ########.fr       */
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
