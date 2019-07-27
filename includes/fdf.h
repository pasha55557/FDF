/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:53:18 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/27 18:38:00 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <fcntl.h>
# include "../minilibx_macos/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct	s_pixel
{
	int			color;
	int			x;
	int			y;
	int			z;
}				t_pixel;

struct			s_size
{
	int			height;
	int			width;
};

typedef struct	s_pixel_data
{
	int	weigth;
	int	x;
	int	y;
	int z;
}				t_pixel_data;

typedef struct			s_mlx
{
	void		*ptr;
	void		*ptr_image;
	void		*window;	
}				t_mlx;

int			from_HEX_to_DEC(char *hex);
int			get_color(char *line);
void		get_pixels(int fd, t_pixel_data *xyz, t_pixel **pixel);
t_pixel		**init_pixel(int fd);
int			sizeof_file(int fd);
#endif