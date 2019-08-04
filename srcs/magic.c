/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:42:41 by dnightwi          #+#    #+#             */
/*   Updated: 2019/08/04 19:32:05 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int		ft_abs(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

void	braz(t_data_cords cord, t_pixel_data max_cords, t_mlx mlx)
{
	int zoom;
	int	a;
	int	b;
	int	sign;
	int	signa;
	int	signb;
	int	f;
	int	x;
	int	y;
	int	x1;
	int	y1;
	int	x0;
	int	y0;

	zoom = max_cords.scale;
	x0 = cord.start_x * zoom; //50 is zoom
	y0 = cord.start_y * zoom;
	x1 = cord.end_x * zoom;
	y1 = cord.end_y * zoom;
	x = x0;
	y = y0;
	a = y1 - y0;
	b = x0 - x1;
	f = 0;
	if (ft_abs(a) > ft_abs(b))
		sign = 1;
	else
		sign = -1;
	if (a < 0)
		signa = -1;
	else
		signa = 1;
	if (b < 0)
		signb = -1;
	else
		signb = 1;
	mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * zoom/4) + x, 540 - (max_cords.y * zoom/2) + y, 16777215);
	if (sign == -1)
	{
		while (x != x1 || y != y1)
		{
			f += a * signa;
			if (ft_abs(f) > ft_abs(f - ft_abs(b)))
			{
				f -= b * signb;
				y += signa;
			}
			x -= signb;
			mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * zoom/4) + x, 540 - (max_cords.y * zoom/2) + y, 16777215);

		}
	}
	else
	{
		while (x != x1 || y != y1)
		{
			f += b * signb;
			if (ft_abs(f) > ft_abs(f - ft_abs(a)))
			{
				f -= a * signa;
				x -= signb;
			}
			y += signa;
			mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * zoom/4) + x, 540 - (max_cords.y * zoom/2) + y, 16777215);
		}
	}
	
}

static void	draw_sides(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int	i;
	int	j;
	t_data_cords	cord;

	i = 0;
	j = 0;
	while (pixel[j * xyz.weight]->y < xyz.y - 1)
	{
		cord.start_x = pixel[xyz.x - 1 + j * xyz.weight]->x;
		cord.start_y = pixel[xyz.x - 1 + j * xyz.weight]->y;
		cord.end_x = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->x;
		cord.end_y = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->y;
		iso(&cord.start_x, &cord.start_y, pixel[xyz.x - 1 + j * xyz.weight]->z);
		iso(&cord.end_x, &cord.end_y, pixel[xyz.x - 1 + (j + 1) * xyz.weight]->z);
		braz(cord, xyz, mlx);
		j++;
	}
	while (pixel[i]->x < xyz.x - 1)
	{
		cord.start_x = pixel[i + (xyz.y - 1) * xyz.weight]->x;
		cord.start_y = pixel[i + (xyz.y - 1) * xyz.weight]->y;
		cord.end_x = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->x;
		cord.end_y = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->y;
		iso(&cord.start_x, &cord.start_y, pixel[i + (xyz.y - 1) * xyz.weight]->z);
		iso(&cord.end_x, &cord.end_y, pixel[i + 1 + (xyz.y - 1) * xyz.weight]->z);
		braz(cord, xyz, mlx);
		i++;
	}
}

static void			draw_vertical(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int				i;
	int				j;
	t_data_cords	cord;

	i = 0;
	while (pixel[i]->x < xyz.x - 1)
	{
		j = 0;
		while (pixel[j * xyz.weight]->y < xyz.y - 1)
		{
			cord.start_x = pixel[i + j * xyz.weight]->x;
			cord.start_y = pixel[i + j * xyz.weight]->y;
			cord.end_x = pixel[i + (j + 1) * xyz.weight]->x;
			cord.end_y = pixel[i + (j + 1) * xyz.weight]->y;
			iso(&cord.start_x, &cord.start_y, pixel[i + j * xyz.weight]->z);
			iso(&cord.end_x, &cord.end_y, pixel[i + (j + 1) * xyz.weight]->z);
			braz(cord, xyz, mlx);
			j++;
		}
		i++;
	}
	draw_sides(pixel, xyz, mlx);
}

void				draw_horizontal(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int				i;
	t_data_cords	cord;

	i = 0;
	while (pixel[i]->y < xyz.y - 1)
	{
		if (pixel[i]->x == xyz.x - 1)
		{
			i++;
			continue;
		}
		cord.start_x = pixel[i]->x;
		cord.start_y = pixel[i]->y;
		cord.end_x = pixel[i + 1]->x;
		cord.end_y = pixel[i + 1]->y;
		iso(&cord.start_x, &cord.start_y, pixel[i]->z);
		iso(&cord.end_x, &cord.end_y, pixel[i + 1]->z);
		braz(cord, xyz, mlx);
		i++;
	}
	draw_vertical(pixel, xyz, mlx);
}
