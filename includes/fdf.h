/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:53:18 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/14 16:45:12 by rsticks          ###   ########.fr       */
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

typedef struct s_data_cords
{
	double	start_x;
	double	start_y;
	double	end_x;
	double	end_y;
	int		start_color;
	int		end_color;
}			t_data_cords;

typedef struct			s_pixel
{
	int					color;
	int					x;
	int					y;
	double				z;
	double				z1;
}						t_pixel;

struct					s_size
{
	int					height;
	int					width;
};

struct					s_max_cords
{
	double				max_x;
	double				max_y;
	double				min_x;
	double				min_y;
};

typedef struct			s_pixel_data
{
	int					weight;
	int					x;
	int					y;
	int					z;
	int 				scale;
	int					min_z;
	int					max_z;
}						t_pixel_data;

typedef struct			s_angle
{
	double				x;
	double				y;
	double				z;
	double				moves_count;
}						t_angle;

typedef struct			s_mlx
{
	void				*ptr;
	void				*ptr_image;
	void				*window;
	int					mv_y;
	int					mv_x;
	t_angle				angle;
}						t_mlx;



typedef struct 			s_dta
{
	t_angle				angle;
	t_pixel				**pixel;
	t_pixel_data		xyz;
	t_mlx				mlx;

}						t_dta;

typedef struct			s_braz
{
	int					a;
	int					b;
	int					sign;
	int					signa;
	int					signb;
	int					f;
	int					x;
	int					y;
	int					x1;
	int					y1;
	int					x0;
	int					y0;
	int					color;
}						t_braz;

int						get_light(int start, int end, double percentage);
double					percent(int start, int end, int avr);
int						ft_abs(int i);
int						get_cur_color(t_pixel current, t_data_cords cord);
double					percent(int start, int end, int current);
int						scale(t_pixel **pixel, t_pixel_data xyz, t_angle);
void					iso(double *x, double *y, double z, t_angle angle);
void					draw_hor_line(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx); // whats that
void					braz(t_data_cords cord, t_pixel_data max_cords, t_mlx mlx);
void					draw_line(t_pixel_data xyz, t_mlx mlx);
int						from_HEX_to_DEC(char *hex);
int						get_color(char *line);
void					get_pixels(int fd, t_pixel_data *xyz, t_pixel **pixel);
t_pixel					**init_pixel(int fd);
void					draw_horizontal(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx, t_angle angle);
int						sizeof_file(int fd, int *color);
#endif