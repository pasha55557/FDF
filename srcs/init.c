/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:47:01 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/27 18:45:56 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pixel		**init_pixel(int fd)
{
	int			size;
	t_pixel		**pixel;

	size = sizeof_file(fd);
	size++;
	pixel = (t_pixel**)malloc(sizeof(t_pixel*) * size);
	while (size)
		pixel[--size] = (t_pixel*)malloc(sizeof(t_pixel));
	return (pixel);
}

int			sizeof_file(int fd)
{
	char				*ptr_line;
	char				*line;
	int					x;
	int					y;

	ptr_line = line;
	y = 0;
	while (get_next_line(fd, &line) == 1)
	{
		x = 0;
		while (*line != '\0')
		{
			if (ft_isdigit(*line))
			{
				x++;
				while (ft_isdigit(*line))
					line++;
			}
			if (*line == ',')
				line = line + 9;
			while (*line == ' ')
				line++;
		}
		y++;
	}
	ft_strdel(&ptr_line);
	close(fd);
	return (x * y);
}