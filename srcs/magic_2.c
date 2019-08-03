/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:29:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/03 19:14:00 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	iso(double *x, double *y, double z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = ((previous_x + previous_y) * sin(0.523599)) - z;
}

/*void		draw_hor_line(t_pixel **pixel, t_pixel_data xyz, t_mlx mlx)
{
	int	y;
	int x;
	int start[2];
	int end[2];

	x = 0;
	y = 0;
	while (y < xyz.y)
	{
		while (x < (xyz.x - 1))
		{
			start[0] = pixel[x + y * xyz.y]->x;
			start[1] = pixel[x + y * xyz.y]->y;
			iso(&start[0], &start[1], pixel[x + y * xyz.y]->z);
			end[0] = pixel[x + y * xyz.y + 1]->x;
			end[1] = pixel[x + y * xyz.y + 1]->y;
			iso(&end[0], &end[1], pixel[x + y * xyz.y + 1]->z);
			braz(start, end, xyz, mlx);
			x++;
		}
		y++;
		x = 0;
	}
}*/

/*void	draw_line(t_pixel_data xyz, t_mlx mlx)
{
	int xyz_start[2];
	int xyz_end[2];

	xyz_start[0] = 10;
	xyz_start[1] = 10;
	xyz_end[0] = 0;
	xyz_end[1] = 0;
	braz(xyz_start, xyz_end, xyz, mlx);
}*/

