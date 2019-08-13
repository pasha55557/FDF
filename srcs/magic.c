/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:42:41 by dnightwi          #+#    #+#             */
/*   Updated: 2019/08/07 18:37:58 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_abs(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

void	draw_1(t_braz *inf, t_pixel *current, t_data_cords cord, t_mlx mlx, t_pixel_data max_cords)
{
	while (inf->x != inf->x1 || inf->y != inf->y1)
	{
		inf->f += inf->a * inf->signa;
		if (ft_abs(inf->f) > ft_abs(inf->f - ft_abs(inf->b)))
		{
			inf->f -= inf->b * inf->signb;
			inf->y += inf->signa;
		}
		inf->x -= inf->signb;
		current->x = inf->x;
		current->y = inf->y;
		current->color = inf->color;
		inf->color = get_cur_color(*current, cord);
		mlx_pixel_put(mlx.ptr, mlx.window, ((960 - (max_cords.x * max_cords.scale/4) + inf->x) + mlx.mv_x), (540 - (max_cords.y * max_cords.scale/2) + inf->y) + mlx.mv_y, inf->color);
	}
}

void	draw_2(t_braz *inf, t_pixel *current, t_data_cords cord, t_mlx mlx, t_pixel_data max_cords)
{
	while (inf->x != inf->x1 || inf->y != inf->y1)
		{
			inf->f += inf->b * inf->signb;
			if (ft_abs(inf->f) > ft_abs(inf->f - ft_abs(inf->a)))
			{
				inf->f -= inf->a * inf->signa;
				inf->x -= inf->signb;
			}
			inf->y += inf->signa;
			current->x = inf->x;
			current->y = inf->y;
			current->color = inf->color;
			inf->color = get_cur_color(*current, cord);
			mlx_pixel_put(mlx.ptr, mlx.window, ((960 - (max_cords.x * max_cords.scale/4) + inf->x) + mlx.mv_x), (540 - (max_cords.y * max_cords.scale/2) + inf->y) + mlx.mv_y, inf->color);
		}
}

void	braz(t_data_cords cord, t_pixel_data max_cords, t_mlx mlx)
{
	t_pixel current;
	t_braz	inf;

	inf.x1 = cord.end_x * max_cords.scale;
	inf.y1 = cord.end_y * max_cords.scale;
	inf.x = cord.start_x * max_cords.scale;
	inf.y = cord.start_y * max_cords.scale;
	inf.a = inf.y1 - inf.y;
	inf.b = inf.x - inf.x1;
	inf.f = 0;
	inf.color = cord.start_color;
	inf.sign = (ft_abs(inf.a) > ft_abs(inf.b)) ? 1 : -1;
	inf.signa = (inf.a < 0) ? -1 : 1;
	inf.signb = (inf.b < 0) ? -1 : 1;
	cord.start_x = inf.x;
	cord.end_x = inf.x1;
	cord.start_y = inf.y;
	cord.end_y = inf.y1;
	mlx_pixel_put(mlx.ptr, mlx.window, ((960 - (max_cords.x * max_cords.scale/4) + inf.x) + mlx.mv_x), (540 - (max_cords.y * max_cords.scale/2) + inf.y) + mlx.mv_y, inf.color);
	if (inf.sign == -1)
		draw_1(&inf, &current, cord, mlx, max_cords);
	else
		draw_2(&inf, &current, cord, mlx, max_cords);
}

static void	draw_sides(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx, t_angle angle)
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
		iso(&cord.start_x, &cord.start_y, pixel[xyz.x - 1 + j * xyz.weight]->z, angle);
		iso(&cord.end_x, &cord.end_y, pixel[xyz.x - 1 + (j + 1) * xyz.weight]->z, angle);
		cord.start_color = pixel[xyz.x - 1 + j * xyz.weight]->color;
		cord.end_color = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->color;
		braz(cord, xyz, mlx);
		j++;
	}
	while (pixel[i]->x < xyz.x - 1)
	{
		cord.start_x = pixel[i + (xyz.y - 1) * xyz.weight]->x;
		cord.start_y = pixel[i + (xyz.y - 1) * xyz.weight]->y;
		cord.end_x = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->x;
		cord.end_y = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->y;
		iso(&cord.start_x, &cord.start_y, pixel[i + (xyz.y - 1) * xyz.weight]->z, angle);
		iso(&cord.end_x, &cord.end_y, pixel[i + 1 + (xyz.y - 1) * xyz.weight]->z, angle);
		cord.start_color = pixel[i + (xyz.y - 1) * xyz.weight]->color;
		cord.end_color = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->color;
		braz(cord, xyz, mlx);
		i++;
	}
}

static void			draw_vertical(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx, t_angle angle)
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
			iso(&cord.start_x, &cord.start_y, pixel[i + j * xyz.weight]->z, angle);
			iso(&cord.end_x, &cord.end_y, pixel[i + (j + 1) * xyz.weight]->z, angle);
			cord.start_color = pixel[i + j * xyz.weight]->color;
			cord.end_color = pixel[i + (j + 1) * xyz.weight]->color;
			braz(cord, xyz, mlx);
			j++;
		}
		i++;
	}
	draw_sides(pixel, xyz, mlx, angle);
}

void				draw_horizontal(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx, t_angle angle)
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
		iso(&cord.start_x, &cord.start_y, pixel[i]->z, angle);
		iso(&cord.end_x, &cord.end_y, pixel[i + 1]->z, angle);
		cord.start_color = pixel[i]->color;
		cord.end_color = pixel[i + 1]->color;
		braz(cord, xyz, mlx);
		i++;
	}
	draw_vertical(pixel, xyz, mlx, angle);
}
