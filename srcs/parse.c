/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:15:16 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 02:55:38 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		in_parse_map(char *line, t_data *data, int i, int j)
{
	if (line[i] != ' ' && line[i + 1] && line[i + 1] != ' ')
		exit_properly(data, 1,
"Les elements de la map doivent etre separes d'un espace au moins.\n");
	if (line[i] == ' ')
	{
		if (line[i] == ' ' && line[i + 1] == ' ' && ++i)
			data->parse.map[data->parse.i][j++] = '0';
		return (0);
	}
	else
		data->parse.map[data->parse.i][j] = line[i];
	if (line[i] == 'N' || line[i] == 'E' ||
			line[i] == 'W' || line[i] == 'S')
	{
		if (data->parse.pos.x > 0)
			exit_properly(data, 1, "Perso a plusieurs positions.\n");
		data->parse.pos.x = data->parse.i;
		data->parse.pos.y = j;
		set_parse_dir(data, line[i]);
		data->parse.map[data->parse.i][j] = '0';
	}
	return (1);
}

void	parsing(char *path, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	check_file_extension(data, path);
	fd = open(path, O_RDONLY);
	init_parse_map(data, path);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		check_all_cases(line, data);
		check_tex(line, data);
		check_floor(line, data);
		check_res(line, data);
		line[0] == '1' ? fill_parse_map(line, data) : 1;
		if (data->parse.check_map == 1 && line[0] != '1')
			exit_properly(data, 1, "Presence de saut de ligne dans la map.\n");
		free(line);
	}
	if (ret == -1)
		exit_properly(data, 1, "l'argument n'est pas un fichier valable\n");
	if ((int)data->parse.pos.x == 0)
		exit_properly(data, 1, "Mauvaise position du joueur.\n");
	*line == 1 ? fill_parse_map(line, data) : 1;
	ret == 0 ? free(line) : 0;
	close(fd);
}
