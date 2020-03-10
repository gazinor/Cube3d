/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:42:55 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/10 02:26:35 by glaurent         ###   ########.fr       */
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
		if (data->w <= 0 || data->h <= 0)
			exit_properly(data, 1,
			"Mauvaises resolutions (1-2560 / 1-1440)\n");
		if (data->w > 2560)
			data->w = 2560;
		if (data->h > 1440)
			data->h = 1440;
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
		!(line[0] == 'C' && line[1] == ' ') && !(line[0] == '0') &&
		!(line[0] == '1') && !(line[0] == '\n') && !(line[0] == ' '))
		exit_properly(data, 1, "element inconnu dans le fichier\n");
}

void	init_parse_map(t_data *data, char *path)
{
	int		fd;
	char	*line;
	int		ret;
	int		debut;

	fd = open(path, O_RDONLY);
	debut = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line == '1' || *line == ' ' || *line == '0')
			++data->parse.nb_line;
		else
			++debut;
		free(line);
	}
	ret == 0 ? free(line) : 1;
	close(fd);
	if (!(data->parse.map = malloc(sizeof(char *) * (data->parse.nb_line + 1))))
		exit_properly(data, 1, "Malloc qui foire.\n");
	malloc_map(data, debut, path);
}

void	malloc_map(t_data *data, int debut, char *path)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;

	fd = open(path, O_RDONLY);
	i = -1;
	while (++i < debut && (ret = get_next_line(fd, &line)) > 0)
		free(line);
	(i = -1) == -1 && ret == 0 ? free(line) : 1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line == '1' || *line == ' ' || *line == '0')
			data->parse.map[++i] = ft_strdup(line);
		else
			exit_properly(data, 1,
		"Les lignes de la map debute par un '1', un '0' ou un espace.\n");
		free(line);
	}
	data->parse.map[++i] = 0;
	ret == 0 ? free(line) : 1;
	close(fd);
	fill_parse_map(ft_tabdup(data->parse.map), data);
}
