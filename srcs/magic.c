/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnightwi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:42:41 by dnightwi          #+#    #+#             */
/*   Updated: 2019/07/30 17:42:44 by dnightwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

static int		ft_abs(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

static void	braz(int *start, int *end, t_pixel_data max_cords, t_mlx mlx)
{
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

	x0 = start[0] * 30; //30 is zoom
	y0 = start[1] * 30;
	x1 = end[0] * 30;
	y1 = end[1] * 30;
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
	mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * 30/2) + ((x - y) * cos(0.523599)), 540 - (max_cords.y * 30/2) + ((x + y) * sin(0.523599)), 0xFF0000);
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
			mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * 30/2) + ((x - y) * cos(0.523599)), 540 - (max_cords.y * 30/2) + ((x + y) * sin(0.523599)), 0xFF0000);

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
			mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * 30/2) + ((x - y) * cos(0.523599)), 540 - (max_cords.y * 30/2) + ((x + y) * sin(0.523599)), 0xFF0000);
		}
	}
	
}

static void	draw_sides(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int	i;
	int	j;
	int	xyz0[3];
	int	xyz1[3];

	i = 0;
	j = 0;
	while (pixel[j * xyz.weight]->y < xyz.y - 1)
	{
		xyz0[0] = pixel[xyz.x - 1 + j * xyz.weight]->x;
		xyz0[2] = pixel[xyz.x - 1 + j * xyz.weight]->z;
		xyz0[1] = pixel[xyz.x - 1 + j * xyz.weight]->y - xyz0[2] * sin(0.523599);
		xyz1[0] = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->x;
		xyz1[2] = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->z;
		xyz1[1] = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->y - xyz1[2] * sin(0.523599);
		braz(xyz0, xyz1, xyz, mlx);
		j++;
	}
	while (pixel[i]->x < xyz.x - 1)
	{
		xyz0[0] = pixel[i + (xyz.y - 1) * xyz.weight]->x;
		xyz0[2] = pixel[i + (xyz.y - 1) * xyz.weight]->z;
		xyz0[1] = pixel[i + (xyz.y - 1) * xyz.weight]->y - xyz0[2] * sin(0.523599);
		xyz1[0] = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->x;
		xyz1[2] = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->z;
		xyz1[1] = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->y - xyz1[2] * sin(0.523599);
		braz(xyz0, xyz1, xyz, mlx);
		i++;
	}
}

static void	draw_vertical(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int	i;
	int	j;
	int	xyz0[3];
	int	xyz1[3];

	i = 0;
	while (pixel[i]->x < xyz.x - 1)
	{
		j = 0;
		while (pixel[j * xyz.weight]->y < xyz.y - 1)
		{
			xyz0[0] = pixel[i + j * xyz.weight]->x;
			xyz0[2] = pixel[i + j * xyz.weight]->z;
			xyz0[1] = pixel[i + j * xyz.weight]->y - xyz0[2] * sin(0.523599);
			xyz1[0] = pixel[i + (j + 1) * xyz.weight]->x;
			xyz1[2] = pixel[i + (j + 1) * xyz.weight]->z;
			xyz1[1] = pixel[i + (j + 1) * xyz.weight]->y - xyz1[2] * sin(0.523599);
			braz(xyz0, xyz1, xyz, mlx);
			j++;
		}
		i++;
	}
	draw_sides(pixel, xyz, mlx);
}

void	draw_horizontal(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int	i;
	int	xyz0[3];
	int	xyz1[3];

	i = 0;
	while (pixel[i]->y < xyz.y - 1)
	{
		if (pixel[i]->x == xyz.x - 1)
		{
			i++;
			continue;
		}
		xyz0[0] = pixel[i]->x;
		xyz0[2] = pixel[i]->z;
		xyz0[1] = pixel[i]->y - xyz0[2] * sin(0.523599);
		xyz1[0] = pixel[i + 1]->x;
		xyz1[2] = pixel[i + 1]->z;
		xyz1[1] = pixel[i + 1]->y - xyz1[2] * sin(0.523599);
		braz(xyz0, xyz1, xyz, mlx);
		i++;
	}
	draw_vertical(pixel, xyz, mlx);
}

