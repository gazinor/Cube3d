/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 01:23:50 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 04:21:04 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (FALSE);
	if (s2[i] != '\0')
		return (FALSE);
	return (TRUE);
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*join_n_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (tmp);
}

void	check_door(t_data *data)
{
	if (data->map[(int)(data->perso.pos.x + (data->perso.dir.x *
					data->perso.speed))][(int)(data->perso.pos.y +
					(data->perso.dir.y * data->perso.speed))] == '3')
		data->map[(int)(data->perso.pos.x + (data->perso.dir.x *
					data->perso.speed))][(int)(data->perso.pos.y +
					(data->perso.dir.y * data->perso.speed))] = '0';
}

void	check_mod(t_data *data)
{
	if (data->option.status == 1)
	{
		if (data->mod.nbr[NORMAL] == 1 && data->mod.light != 5)
			data->mod.light = 5;
		if (data->mod.nbr[DARK] == 1 && data->mod.light != 1)
			data->mod.light = 0.5;
		if (data->mod.nbr[MIRROR] == 1 && data->mod.light != 5)
			data->mod.light = 5;
	}
}
