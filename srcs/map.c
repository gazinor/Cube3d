/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:12:13 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/05 00:52:44 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char    *G_BUFFER[11] =
{
	"1111111111111",
	"1000000000001",
	"100N000000001",
	"1000000000001",
	"1000000000001",
	"1000000000001",
	"1000000000001",
	"1000000000001",
	"1000000000001",
	"1111111111111"
};

void    *ft_init_map(t_data *data)
{
	int i;
	int j;

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

void    ft_fill_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (G_BUFFER[i])
	{
		j = 0;
		while (G_BUFFER[i][j])
		{
			data->map[i][j] = G_BUFFER[i][j];
			if (G_BUFFER[i][j] == 'N' || G_BUFFER[i][j] == 'S' ||
					G_BUFFER[i][j] == 'E' || G_BUFFER[i][j] == 'O')
			{
				data->map[i][j] = '0';
				data->perso.pos.x = (double)i + 0.5;
				data->perso.pos.y = (double)j + 0.5;
			}
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
}
