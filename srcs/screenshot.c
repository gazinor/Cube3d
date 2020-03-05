/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 05:34:57 by glaurent          #+#    #+#             */
/*   Updated: 2020/03/05 06:42:54 by glaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		my_abs(double value)
{
	if (value == 0)
		value = 0.1;
	else if (value < 0)
		value = -value;
	return (value);
}

static void	int_in_char(unsigned char *str, int value)
{
	int i;

	i = -1;
	while (++i < 4)
		str[i] = (unsigned char)(value >> (i * 8));
}

static int	write_header(int fd, unsigned int fd_size, t_data *data)
{
	unsigned char	header[54];
	int				i;

	i = -1;
	while (++i < 54)
		header[i] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_in_char(header + 2, fd_size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_in_char(header + 18, data->w);
	int_in_char(header + 22, -data->h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (write(fd, header, 54));
}

static int	write_screen(t_data *data, int fd, unsigned int pad_byte_row)
{
	const unsigned char	zeroes[3] = {0, 0, 0};
	int					y;
	int					x;

	y = -1;
	while (++y < data->h)
	{
		x = -1;
		while (++x < data->w)
			if (write(fd, &data->img.buffer[y * data->w + x], 3) < 0)
				return (0);
		if (write(fd, &zeroes, pad_byte_row) < 0)
			return (0);
	}
	return (1);
}

void		screenshot(t_data *data)
{
	int				fd;
	unsigned int	fd_size;
	unsigned int	pxl_byte_row;
	unsigned int	pad_byte_row;

	pxl_byte_row = data->w * 3;
	pad_byte_row = (4 - (pxl_byte_row % 4)) % 4;
	fd_size = 54 + (pxl_byte_row + pad_byte_row) * data->h;
	if ((fd = open("./screenshot/screenshot.bmp", O_WRONLY | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		write(2, "error\n", 6);
	if (write_header(fd, fd_size, data) < 0)
		write(2, "error\n", 6);
	if (!write_screen(data, fd, pad_byte_row))
		write(2, "error\n", 6);
	close(fd);
}
