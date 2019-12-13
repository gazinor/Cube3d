/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:12:13 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/13 03:13:51 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*G_BUFFER[100] =
{
	"1111111111111111111111111111111111111111",
	"1000000000100000000000100000000100000001",
	"1000000000100000000000100000000100000001",
	"1000000000100000000000100000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1111000000100000000000000000000100000001",
	"1001000000100000000000000000000100000001",
	"1011000000100000000000000000000100000001",
	"1010000000100001111100000000000100000001",
	"1010000000100010000011100000000100000001",
	"1011111111110100111000011100000111111111",
	"1000100010000001000100100010000000000001",
	"1110111010100011010000000010000000000001",
	"1000000000110101001144110010000000000001",
	"1011111111000001010000001010000000000001",
	"1000000000010111001000010011111000000001",
	"1111111111100000100000000100000111111111",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000004000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1000000000100000000000000000000100000001",
	"1111111111100000000000000000000111111111",
	"1000000000000000000000000000000000000001",
	"1000000000000000000000000000000000000001",
	"1000000000000000000000000000000000000001",
	"100000000000000000N000000000000000000001",
	"1000000000000000000000000000000000000001",
	"1111111111100000011111111111141111111111",
	"10000000001000000100000000000001",
	"10000000001000000100000000000001",
	"10000000001000000100000000000001",
	"10000000001000000111111100000001",
	"10000000001000000000000011110001",
	"10000000001111111111110000010001",
	"10000000001000000000000000010001",
	"10000000001000000000000010000001",
	"10000000001000000000000010000001",
	"10000000001010000000000010000001",
	"10000000001111000000000010000001",
	"10000000001010000000000010000001",
	"1111111111100000000000001111111111111111",
	"1000000000100000000000000000000000000001",
	"1000000000000001000000010000000000000001",
	"1000000000100000000000010000000000000001",
	"1000000000100000000000010000000000000001",
	"1000000000100000000000010000000000000001",
	"1111111111111110111111111111111111111111",
	"11111111111111131111111111111",
	"10000000001100000000000000001",
	"10110000011100000000000010001",
	"10010000000000000000000010001",
	"10110000011100000000000010001",
	"10000000001100000111011110001",
	"11110111111111011100000010001",
	"11110111111111011101010010001",
	"11000000110101011100000010001",
	"10000000000000001100000010001",
	"10000000000000001101010010001",
	"11000000110101011111011110001",
	"11110111111101011111011110001",
	"11111111111111111111111111111"
};

void	set_dir(t_data *data, char c)
{
	data->perso.dir.x = -1 * (c == 'S' ? -1 : c == 'N');
	data->perso.dir.y = -1 * (c == 'E' ? -1 : c == 'W');
	data->perso.planx = 0.66 * (c == 'W' ? -1 : c == 'E');
	data->perso.plany = 0.66 * (c == 'S' ? -1 : c == 'N');
}

void	*ft_init_map(t_data *data)
{
	int	i;
	int	j;

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

void	ft_fill_map(t_data *data)
{
	int	i;
	int	j;

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
				set_dir(data, G_BUFFER[i][j]);
				data->map[i][j] = '0';
				data->perso.pos.x = (double)i + 0.5;
				data->perso.pos.y = (double)j + 0.5;
				data->perso.depart.x = (double)i + 0.5;
				data->perso.depart.y = (double)j + 0.5;
			}
			j++;
		}
		data->map[i][j] = '\0';
		i++;
	}
}
