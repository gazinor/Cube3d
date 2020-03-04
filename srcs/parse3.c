/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:42:55 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 02:53:52 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_extension(t_data *data, char *path)
{
	int		i;

	i = 0;
	while (path[i])
		++i;
	if (i > 4 && ft_strcmp(path + i - 4, ".cub"))
		return ;
	exit_properly(data, 1, "Mauvaise extension de fichier('.cub').\n");
}

void	check_res(char *line, t_data *data)
{
	if (line[0] == 'R' && line[1] == ' ')
	{
		if (data->parse.check_r == TRUE)
			exit_properly(data, 1, "2x R arg.\n");
		data->parse.check_r = TRUE;
		ft_atoi_parse(line + (ft_atoi_parse(line + 1, &data->w,
		data)) + 1, &data->h, data);
		if (data->w > 2560 || data->h > 1440 || data->w < 0 || data->h < 0)
			exit_properly(data, 1,
			"Resolutions sup. a la taille de l'ecran (0-2560 / 0-1440)\n");
	}
}

void	check_all_cases(char *line, t_data *data)
{
	if (!line[0])
		return ;
	if (!(line[0] == 'R' && line[1] == ' ') &&
		!(line[0] == 'N' && line[1] == 'O' && line[2] == ' ') &&
		!(line[0] == 'E' && line[1] == 'A' && line[2] == ' ') &&
		!(line[0] == 'S' && line[1] == 'O' && line[2] == ' ') &&
		!(line[0] == 'W' && line[1] == 'E' && line[2] == ' ') &&
		!(line[0] == 'S' && line[1] == ' ') &&
		!(line[0] == 'F' && line[1] == ' ') &&
		!(line[0] == 'C' && line[1] == ' ') &&
		!(line[0] == '1') && !(line[0] == '\n'))
		exit_properly(data, 1, "element inconnu dans le fichier\n");
}

void	init_parse_map(t_data *data, char *path)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;

	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = -1;
		if (*line == '1' && ++data->parse.nb_line)
			if (data->parse.sizeline == 0)
				while (line[++i])
				{
					if ((line[i] != '1' && line[i] != ' ') ||
						(line[i] == ' ' && line[i + 1] && line[i + 1] == ' '))
						exit_properly(data, 1, "Only '1' on first line.\n");
					if (line[i] == '1' || (line[i] == 32 && line[i + 1] == 32))
						++data->parse.sizeline;
				}
		free(line);
	}
	ret == 0 ? free(line) : 1;
	close(fd);
	malloc_map(data);
}

void	malloc_map(t_data *data)
{
	int		i;

	i = -1;
	data->parse.i = 0;
	if (!(data->parse.map = malloc(sizeof(char *) * (data->parse.nb_line + 1))))
		exit_properly(data, 1, "Malloc qui foire.\n");
	while (++i < data->parse.nb_line)
		if (!(data->parse.map[i] = malloc(sizeof(char) *
				(data->parse.sizeline + 1))))
			exit_properly(data, 1, "Malloc qui foire.\n");
	data->parse.map[i] = 0;
}
