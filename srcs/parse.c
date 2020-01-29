/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:15:16 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/29 08:07:11 by glaurent         ###   ########.fr       */
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
	str[i] == '-' ? exit_properly(data, 1,
		"Pas de nombres negatifs hein 😉\n") : 1;
	!(str[i] >= '0' && str[i] <= '9') ?	exit_properly(data, 1,
		"Mauvais prototype, les nombres ne sont pas tous corrects.\n") : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		++i;
	}
	if (str[i] != '\0' && str[i] != ' ' && str[i] != ',')
		exit_properly(data, 1, "Mauvais caracteres en fin de nombre.\n");
	*res = nb;
	return (i);
}

t_img	*get_img(char *line, t_data *data)
{
	if (line[0] == 'S' && line[1] == ' ')
	{
		data->parse.check_s = TRUE;
		return (&data->parse.sprite_text);
	}
	else if (line[0] == 'N' || line[0] == 'S')
		return ((line[0] == 'N') ? &data->parse.ntext : &data->parse.stext);
	else
		return ((line[0] == 'W') ? &data->parse.wtext : &data->parse.etext);
}

void	check_tex(char *line, t_data *data)
{	
	t_img	*img;
	int		i;

	i = 0;
	if ((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O'
) || (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' && line[1] == 'A')
				|| (line[0] == 'S' && line[1] == ' '))
	{
		img = get_img(line, data);
		if (img->check == TRUE)
			exit_properly(data, 1, "Texture en double.\n");
		while ((line[i] >= 'A' && line[i] <= 'Z') ||
				line[i] == '\t' || line[i] == ' ')
			++i;
		if ((open(line + i, O_RDONLY)) == -1)
			exit_properly(data, 1, "Mauvais nom de fichier de texture.\n");
		img->filename = line + i;
		load_image(data, img, 1000, 1000);
	}
}

void	check_pixel(t_data *data, int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255)
		exit_properly(data, 1,
			"Mauvais composants de pixel. Doit etre contenu entre 0 et 255.\n");
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
		data->parse.check_f == TRUE ? exit_properly(data, 1, "2x F arg.\n") : 1;
		i += ft_atoi_parse(line + i, &r, data);
		i += ft_atoi_parse(line + i, &g, data);
		i += ft_atoi_parse(line + i, &b, data);
		check_pixel(data, r, g, b);
		data->parse.f_color = (r << 16) + (g << 8) + b;
		data->parse.check_f = TRUE;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		data->parse.check_c == TRUE ? exit_properly(data, 1, "2x C arg.\n") : 1;
		i += ft_atoi_parse(line + i, &r, data);
		i += ft_atoi_parse(line + i, &g, data);
		i += ft_atoi_parse(line + i, &b, data);
		check_pixel(data, r, g, b);
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
			exit_properly(data, 1, "Manque d'element dans le fichier, \
ou ne sont-ils pas dans le bon ordre ? Corrige ca.\n");
		data->parse.check_map = TRUE;
	}
}

int		ft_strlen_map(t_data *data, char *str)
{
	int		i;
	int		count;
	int		token;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (data->parse.i == data->parse.nb_line - 1 &&
				str[i] != '1' && str[i] != ' ')
			exit_properly(data, 1, "Only '1' on last line.\n");
		if (str[i] == '1' || str[i] == '0' || str[i] == '2' || str[i] == 'N' ||
			str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			token = i;
			count++;
		}
		else if (str[i] == ' ')
			continue ;
		else
			exit_properly(data, 1, 
			"Mauvais caractere dans la map (seulement : 0,1,2,N,S,W,E).\n");
	}
	str[token] != '1' ? exit_properly(data, 1, "Lines must end by '1'.\n") : 1;
	return (count);
}

void	set_parse_dir(t_data *data, char c)
{
    data->parse.dir.x = -1 * (c == 'S' ? -1 : c == 'N');
    data->parse.dir.y = -1 * (c == 'E' ? -1 : c == 'W');
    data->parse.planx = 0.66 * (c == 'W' ? -1 : c == 'E');
    data->parse.plany = 0.66 * (c == 'S' ? -1 : c == 'N');
}

void	fill_parse_map(char *line, t_data *data)
{
	int		i;
	int		j;

	check_parse_map(data);
	i = -1;
	j = 0;
	if (ft_strlen_map(data, line) != data->parse.sizeline)
		exit_properly(data, 1, "La map doit etre rectangle.\n");
	while (line[++i])
		if (line[i] == '1' || line[i] == '0' || line[i] == '2' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			data->parse.map[data->parse.i][j] = line[i];
			if (line[i] == 'N' || line[i] == 'S' ||
				line[i] == 'E' || line[i] == 'W')
			{
				data->parse.pos.x = data->parse.i;
				data->parse.pos.y = j;
				set_parse_dir(data, line[i]);
				data->parse.map[data->parse.i][j] = '0';
			}
			++j;
		}
	data->parse.map[data->parse.i][j] = '\0';
	++data->parse.i;
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
						exit_properly(data, 1, "Only '1' on first line.\n");
					line[i] == '1' ? ++data->parse.sizeline : 1;
				}
			++data->parse.nb_line;
		}	
		free(line);
	}
	ret == 0 ? free(line) : 1;
	close(fd);
	malloc_map(data);
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
			exit_properly(data, 1, "Resolutions sup. a la taille de l'ecran\n");
	}
}

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
		check_floor_n_sky(line, data);
		check_res(line, data);
		line[0] == '1' ? fill_parse_map(line, data) : 1;
		if (data->parse.check_map == 1 && line[0] != '1')
			exit_properly(data, 1, "Pas de \\n dans la map, merci.\n");
		free(line);
	}
	if (ret == -1)
		exit_properly(data, 1, "l'argument n'est pas un fichier valable\n"); 
	*line == 1 ? fill_parse_map(line, data) : 1;
	ret == 0 ? free(line) : 0;
	close(fd);
}
