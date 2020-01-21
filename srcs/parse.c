/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:15:16 by glaurent          #+#    #+#             */
/*   Updated: 2020/01/21 08:57:20 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_parse(char *str, int *res)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] == '\t' || str[i] == ' ' || str[i] == ',')
		++i;
	if (!(str[i] >= '0' && str[i] <= '9'))
	{
		printf("mauvais prototype, ce n'est pas un nombre\n");
		exit(0);
	}
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
		{
			printf("mauvais nom de fichier de texture\n");
			exit(0);
		}
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
		i += ft_atoi_parse(line + i, &r);
		i += ft_atoi_parse(line + i, &g);
		i += ft_atoi_parse(line + i, &b);
		data->parse.f_color = (r << 16) + (g << 8) + b;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		i += ft_atoi_parse(line + i, &r);
		i += ft_atoi_parse(line + i, &g);
		i += ft_atoi_parse(line + i, &b);
		data->parse.c_color = (r << 16) + (g << 8) + b;
	}
}

void	parsing(char *path, t_data *data)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;

	fd = open(path, O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = 0;
		check_tex(line, data);
		check_floor_n_sky(line, data);
		if (line[0] == 'R')
		{
			i += ft_atoi_parse(line + i + 1, &data->parse.width);
			i += ft_atoi_parse(line + i + 1, &data->parse.height);
		}
		free(line);
	}
	if (ret == -1)
	{
		printf("mauvais fichier\n");
		exit(0);
	}
	printf("fin du parsing\n");
}
