   /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:59:34 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/12 18:03:54 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	move_z(t_dta **data, int move)
{
	int i;

	i = 0;
	while (i < (*data)->xyz.x * (*data)->xyz.y)
	{
		if ((*data)->pixel[i]->z != 0 && (*data)->pixel[i]->z + move > 0)
			(*data)->pixel[i]->z *= move;
		i++;
	}
}

/*void	x_rotation(t_dta **data)
{
	int	i;
	double	dz;
	double	dy;

	i = 0;
	while (i < (*data)->xyz.x * (*data)->xyz.y)
	{
		dy = (*data)->pixel[i]->y * cos((*data)->mlx.angle_x) + (*data)->pixel[i]->z * sin((*data)->mlx.angle_x);
		dz = -(*data)->pixel[i]->y * sin((*data)->mlx.angle_x) + (*data)->pixel[i]->z * cos((*data)->mlx.angle_x);
		(*data)->pixel[i]->y = dy;
		(*data)->pixel[i]->z = dz;
		i++;
	}
}*/

int		key_hook(int key, t_dta *data)
{
	if (key == 53)
		exit(1); //need to clean everything before exit
	else if (key == 69)  //when plus on numpad is pressed, zoom in (+) image
		data->xyz.scale += 1;
	else if (key == 78 && data->xyz.scale - 1 >= 0) //when minus on numpad is pressed, zoom out (-) image
		data->xyz.scale -= 1;
	else if (key == 18) //press 1 to increase z
		move_z(&data, 2);
	else if (key == 19) //press 2 to decrease z
		move_z(&data, -2);
	else if (key == 126) //press up (on the arrows) to move image upper
		data->mlx.mv_y += -5;
	else if (key == 125)
		data->mlx.mv_y += 5;
	else if (key == 123)
		data->mlx.mv_x += -5;
	else if (key == 124)
		data->mlx.mv_x += 5;
	else if (key == 13) //w
		data->angle.x -= 0.01;
	else if (key == 1) //s
		data->angle.x += 0.01;
	else if (key == 0) //a 
		data->angle.y += 0.01;
	else if (key == 2) //d
		data->angle.y -= 0.01;
	else if (key == 25)
		data->angle.z += 0.01; //9
	else if (key == 29)
		data->angle.z -= 0.01; //0
	mlx_clear_window(data->mlx.ptr, data->mlx.window);
	draw_horizontal(data->pixel, data->xyz, data->mlx, data->angle);
	return (0);
}

int		main(int argc, char **argv)
{
	t_pixel				**pixel;
	struct s_size		size;
	t_pixel_data		xyz;
	t_mlx				mlx;
	int					fd;
	int					zoom;
	t_dta				*data;
	t_angle				angle;


	/*size.height = 0; trash, programm works perfectly fine without it
	xyz.x = 0;
	xyz.y = 0;
	xyz.z = 0;*/
	if (argc != 2)
	{
		ft_putendl("Валидация: пиздец, карты нет"); //write usage, also add error if fd is incorrect
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	pixel = init_pixel(fd);
	fd = open(argv[1], O_RDONLY);
	ft_putstr("file is open\n");
	get_pixels(fd, &xyz, pixel);
	printf("координаты записаны\n");
	xyz.scale = scale(pixel, xyz);

	angle.x = 0;
	angle.y = 0;
	angle.z = 0;
	mlx.mv_x = 0;
	mlx.mv_y = 0;
	data = (t_dta*)malloc(sizeof(t_dta));
	printf("zoom is calculeted\n");
	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, 1920, 1080, "FDF");
	draw_horizontal(pixel, xyz, mlx, angle);
	//good way to store information
	data->pixel = pixel;
	data->mlx = mlx;
	data->xyz = xyz;
	data->angle = angle;


	mlx_hook(mlx.window, 2, 0, (int (*)())key_hook, data);
	mlx_loop(mlx.ptr);
	return (0);
}
