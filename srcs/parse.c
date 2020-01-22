/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:15:16 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/22 12:40:30 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_parse(char *str, int *res, t_data *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == ',')
		++i;
	if (!(str[i] >= '0' && str[i] <= '9'))
		exit_properly(data, 1, "mauvais prototype, ce n'est pas un nombre\n");
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		++i;
	}
	*res = nb;
	return (i);
}

void	check_tex(char *line, t_data *data)
{	
	t_img	*img;
	int		i;

	i = 0;
	img = NULL;
	if (((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O'
) || (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' && line[1] == 'A'))
		&& line[2] == ' ')
	{
		if (line[0] == 'N' || line[0] == 'S')
			img = (line[0] == 'N') ? &data->parse.ntext : &data->parse.stext;
		else if (line[0] == 'S' && line[1] == ' ')
			img = &data->parse.sprite_text;
		else
			img = (line[0] == 'W') ? &data->parse.wtext : &data->parse.etext;
		while ((line[i] >= 'A' && line[i] <= 'Z') ||
				line[i] == '\t' || line[i] == ' ')
			++i;
		if ((open(line + i, O_RDONLY)) == -1)
			exit_properly(data, 1, "mauvais nom de fichier de texture\n");
		img->filename = line + i;
		load_image(data, img, 1000, 1000);
	}
}

void	check_floor_n_sky(char *line, t_data *data)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	if (line[0] == 'F' && line [1] == ' ')
	{
		i += ft_atoi_parse(line + i, &r, data);
		i += ft_atoi_parse(line + i, &g, data);
		i += ft_atoi_parse(line + i, &b, data);
		data->parse.f_color = (r << 16) + (g << 8) + b;
		data->parse.check_f = TRUE;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		i += ft_atoi_parse(line + i, &r, data);
		i += ft_atoi_parse(line + i, &g, data);
		i += ft_atoi_parse(line + i, &b, data);
		data->parse.c_color = (r << 16) + (g << 8) + b;
		data->parse.check_c = TRUE;
	}
}

void	check_parse_map(t_data *data)
{
	if (!data->parse.check_map)
	{
		if (!data->parse.check_r || !data->parse.check_s || !data->parse.check_f
|| !data->parse.check_c || !data->parse.ntext.check || !data->parse.etext.check
			|| !data->parse.stext.check || !data->parse.wtext.check)
			exit_properly(data, 1, "manque d'element dans le fichier\n");
		data->parse.check_map = TRUE;
	}
}

void	fill_parse_map(char *line, t_data *data)
{
	check_parse_map(data);
	while (*line)
	{
		if (*line == '0' || *line == '1')
		{
			**data->parse.map = *line;
			++*data->parse.map;
		}
		++*line;
	}
	++data->parse.map;
}

//					if ((*line != '0' && *line != '1' && *line != ' ') ||
//	((*line == '0' || *line == '1') && (*line + 1 == '0' || *line + 1 == '1'))
//						|| (*line == ' ' && *line + 1 == ' '))
//						exit_properly(data, 1, "mauvaise map (ex : 1 0 0 1)\n");

void	malloc_map(t_data *data)
{
	int		i;

	i = -1;
	if (!(data->parse.map = malloc(sizeof(char *) * (data->parse.nb_line + 1))))
		exit_properly(data, 1, "malloc qui foire\n");
	while (++i < data->parse.nb_line)
		if (!(data->parse.map[i] = malloc(sizeof(char) *
				(data->parse.sizeline + 1))))
			exit_properly(data, 1, "malloc qui foire\n");
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
		if (*line == '1')
		{
			i = -1;
			if (data->parse.sizeline == 0)
				while (line[++i])
				{
					if (line[i] != '1' && line [i] != ' ')
						exit_properly(data, 1, "map n'a pas que des 1 en premiere ligne\n");
					++data->parse.sizeline;
				}
			++data->parse.nb_line;
		}	
		free(line);
	}
	ret == 0 ? free(line) : 1;
	close(fd);
	malloc_map(data);
}

void	parsing(char *path, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(path, O_RDONLY);
	init_parse_map(data, path);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		check_tex(line, data);
		check_floor_n_sky(line, data);
		if (line[0] == 'R' && line[1] == ' ')
		{
			ft_atoi_parse(line + (ft_atoi_parse(line + 1, &data->parse.width,
			data)) + 1, &data->parse.height, data);
			data->parse.check_r = TRUE;
		}
		line[0] == '1' ? fill_parse_map(line, data) : 1;
		free(line);
	}
	ret == 0 ? free(line) : 1;
	if (ret == -1)
		exit_properly(data, 1, "l'argument n'est pas un fichier valable\n"); 
	close(fd);
}
