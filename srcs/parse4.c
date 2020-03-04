/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:51:00 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 02:53:22 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_parse_map(char *line, t_data *data)
{
	int		i;
	int		j;

	check_parse_map(data);
	i = -1;
	j = 0;
	if (ft_strlen_map(data, line, 0) != data->parse.sizeline)
		exit_properly(data, 1, "La map doit etre rectangle.\n");
	while (line[++i])
		if (line[i] == '1' || line[i] == '0' || line[i] == '2' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == ' ')
		{
			if (!in_parse_map(line, data, i, j))
				continue ;
			++j;
		}
	data->parse.map[data->parse.i++][j] = '\0';
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

void	check_parse_map(t_data *data)
{
	if (!data->parse.check_map)
	{
		if (!data->parse.check_r || !data->parse.check_s || !data->parse.check_f
		|| !data->parse.check_c || !data->parse.ntext.check ||
		!data->parse.etext.check || !data->parse.stext.check ||
		!data->parse.wtext.check)
			exit_properly(data, 1, "Manque d'element dans le fichier, \
ou ne sont-ils pas dans le bon ordre ? Corrige ca.\n");
		data->parse.check_map = TRUE;
	}
}

int		ft_strlen_map(t_data *data, char *str, int token)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (data->parse.i == data->parse.nb_line - 1 && ((str[i] != '1' &&
		str[i] != ' ') || (str[i] == ' ' && str[i + 1] && str[i + 1] == ' ')))
			exit_properly(data, 1, "Only '1' on last line.\n");
		if (str[i] == '1' || str[i] == '0' || str[i] == '2' || str[i] == 'N' ||
			str[i] == 'S' || str[i] == 'E' || str[i] == 'W' || str[i] == ' ')
		{
			if ((str[i] == ' ' && str[i + 1] != ' ') ||
				(str[i] == ' ' && str[i + 1] == ' ' && ++count && ++i))
				continue ;
			token = i;
			count++;
		}
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
