/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:29:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/11 15:26:46 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	iso(double *x, double *y, double z, t_angle angle)
{
    double previous_x;
    double previous_y;
	double	previous_z;

    previous_x = *x;
    previous_y = *y;
	previous_z = z;
	if (angle.x != 0)
	{
		*y = previous_y * cos(angle.x) + previous_z * sin(angle.x);
		z = -previous_y * sin(angle.x) + previous_z * cos(angle.x);
		previous_y = *y;
		previous_z = z;
	}
	if (angle.y != 0)
	{
		*x = previous_x * cos(angle.y) + previous_z * sin(angle.y);
		z = -previous_x * sin(angle.y) + previous_z * cos(angle.y);
		previous_x = *x;
		previous_z = z;
	}
	if (angle.z != 0)
	{
		*x = previous_x * cos(angle.z) - previous_y * sin(angle.z);
		*y = previous_x * sin(angle.z) + previous_y * cos(angle.z);
		previous_x = *x;
		previous_y = *y;
	}
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = ((previous_x + previous_y) * sin(0.523599)) - z;
}

int		scale(t_pixel **pixel, t_pixel_data xyz)
{
	struct	s_max_cords	max_cords;
	int		i;
	double	x;
	double	y;
	int		del_x;
	int		del_y;
	int		scale[2];

	max_cords.max_x = 0;
	max_cords.max_y = 0;
	max_cords.min_x = 1920;
	max_cords.min_y = 1080;
	i = 0;
	while (i < ((xyz.x) * (xyz.y)))
	{
		x = pixel[i]->x;
		y = pixel[i]->y;
		//iso(&x, &y, pixel[i]->z);
		x = 960 - xyz.x + x;
		y = 540 - xyz.y/2 + y;
		if (max_cords.max_x < x)
			max_cords.max_x = x;
		if (max_cords.max_y < y)
			max_cords.max_y = y;
		if (max_cords.min_x > x)
			max_cords.min_x = x;
		if (max_cords.min_y > y)
			max_cords.min_y = y;
		i++;
	}
	del_x = max_cords.max_x - max_cords.min_x;
	del_y = max_cords.max_y - max_cords.min_y;
	scale[0] = 1536 / del_x;
	scale[1] = 810 / del_y;
	if (scale[0] > scale[1])
		scale[0] = scale[1];
	printf("zoom = %d\n", scale[0]);
		return(scale[0]);
}

double		percent(int start, int end, int avr)
{
    double placement;
    double distance;

    placement = avr - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int get_cur_color(t_pixel current, t_data_cords cord)
{
    int     red;
    int     green;
    int     blue;
    double  percentage;
	t_pixel	delta;

	delta.x = ft_abs(cord.start_x - cord.end_x);
	delta.y = ft_abs(cord.start_y - cord.end_y);
    if (current.color == cord.end_color)
        return (current.color);
    if (delta.x > delta.y)
        percentage = percent(cord.start_x, cord.end_x, current.x);
    else
        percentage = percent(cord.start_y, cord.end_y, current.y);
    red = get_light((cord.start_color >> 16) & 0xFF, (cord.end_color >> 16) & 0xFF, percentage);
    green = get_light((cord.start_color >> 8) & 0xFF, (cord.end_color >> 8) & 0xFF, percentage);
    blue = get_light(cord.start_color & 0xFF, cord.end_color & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}