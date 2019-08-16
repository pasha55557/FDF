/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:47:01 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/16 18:49:09 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	sizeof_file(int fd, int *color, int y)
{
	char				*ptr_line;
	char				*line;

	while (get_next_line(fd, &line) == 1 && y++)
	{
		ptr_line = line;
		while (*line != '\0' && ++y)
		{
			if (ft_isdigit(*line))
				while (ft_isdigit(*line))
					line++;
			if (*line == ',')
			{
				*color = 1;
				while (!(ft_isspace(*line) || *line == '\0'))
					line++;
			}
			while (ft_isspace(*line))
				line++;
		}
		ft_strdel(&ptr_line);
	}
	ft_strdel(&line);
	return (y);
}

t_pixel		**init_pixel(int fd)
{
	int			color_id;
	int			size;
	t_pixel		**pixel;

	color_id = 0;
	size = sizeof_file(fd, &color_id, -1);
	size++;
	pixel = (t_pixel**)malloc(sizeof(t_pixel*) * size);
	while (size)
		pixel[--size] = (t_pixel*)malloc(sizeof(t_pixel));
	pixel[0]->color = color_id;
	close(fd);
	return (pixel);
}
