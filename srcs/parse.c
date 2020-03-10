/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:15:16 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/10 02:37:56 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		in_parse_map(char *line, t_data *data, int i, int j)
{
	if (line[j] == ' ')
		data->parse.map[i][j] = '0';
	if (line[j] == 'N' || line[j] == 'E' ||
			line[j] == 'W' || line[j] == 'S')
	{
		if (data->parse.pos.x > 0)
			exit_properly(data, 1, "Perso a plusieurs positions.\n");
		data->parse.pos.x = i + 0.5;
		data->parse.pos.y = j + 0.5;
		set_parse_dir(data, line[j]);
		data->parse.map[i][j] = '0';
	}
	return (1);
}

t_pos	int_to_t_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

void	flood_fill(t_data *data, char **map, t_pos pos, int *max)
{
	if (pos.x < data->parse.nb_line && pos.x >= 0 && pos.x <= max[(int)pos.x] &&
			pos.y >= 0 && pos.y <= max[(int)pos.x])
	{
		if (map[(int)pos.x][(int)pos.y] != '1' &&
				map[(int)pos.x][(int)pos.y] != '~')
		{
			map[(int)pos.x][(int)pos.y] = '~';
			flood_fill(data, map, int_to_t_pos(pos.x, pos.y + 1), max);
			flood_fill(data, map, int_to_t_pos(pos.x + 1, pos.y), max);
			flood_fill(data, map, int_to_t_pos(pos.x, pos.y - 1), max);
			flood_fill(data, map, int_to_t_pos(pos.x - 1, pos.y), max);
		}
	}
	else
		exit_properly(data, 1, "Map ouverte.\n");
}

void	parsing(char *path, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	check_file_extension(data, path);
	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		check_all_cases(line, data);
		check_tex(line, data);
		check_floor(line, data);
		check_res(line, data);
		line[0] == '1' || line[0] == ' ' || line[0] == '0' ?
													check_parse_map(data) : 1;
		free(line);
	}
	close(fd);
	init_parse_map(data, path);
	if (ret == -1)
		exit_properly(data, 1, "L'argument n'est pas un fichier valable\n");
	if ((int)data->parse.pos.x == 0)
		exit_properly(data, 1, "Mauvaise position du joueur.\n");
	ret == 0 && (data->begin = TRUE) ? free(line) : 0;
}
