/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 01:59:24 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/04 02:40:17 by glaurent         ###   ########.fr       */
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
	!(str[i] >= '0' && str[i] <= '9') ? exit_properly(data, 1,
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

void	check_pixel(t_data *data, int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255)
		exit_properly(data, 1,
			"Mauvais composants de pixel. Doit etre contenu entre 0 et 255.\n");
}

void	check_sky(char *line, t_data *data)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	if (line[0] == 'C' && line[1] == ' ')
	{
		data->parse.check_c == TRUE ? exit_properly(data, 1, "2x C arg.\n") : 1;
		i += ft_atoi_parse(line + i, &r, data);
		i += ft_atoi_parse(line + i, &g, data);
		i += ft_atoi_parse(line + i, &b, data);
		--i;
		while (line[++i])
			if (line[i] != ' ' || line[i] != '\t')
				exit_properly(data, 1, "Pas plus de trois composantes pour les\
couleurs de pixel\n");
		check_pixel(data, r, g, b);
		data->parse.c_color = (r << 16) + (g << 8) + b;
		data->parse.check_c = TRUE;
	}
}

void	check_floor(char *line, t_data *data)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	if (line[0] == 'F' && line[1] == ' ')
	{
		data->parse.check_f == TRUE ? exit_properly(data, 1, "2x F arg.\n") : 1;
		i += ft_atoi_parse(line + i, &r, data);
		i += ft_atoi_parse(line + i, &g, data);
		i += ft_atoi_parse(line + i, &b, data);
		--i;
		while (line[++i])
			if (line[i] != ' ' || line[i] != '\t')
				exit_properly(data, 1, "Pas plus de trois composantes pour les\
couleurs de pixel\n");
		check_pixel(data, r, g, b);
		data->parse.f_color = (r << 16) + (g << 8) + b;
		data->parse.check_f = TRUE;
	}
	else
		check_sky(line, data);
}
