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

void	move_z(t_dta **data)
{
	int i;

	i = 0;
	(*data)->angle.moves_count += 0.03;
	while (i < (*data)->xyz.x * (*data)->xyz.y)
	{
		(*data)->pixel[i]->z = (*data)->angle.moves_count * (*data)->pixel[i]->z1;
		i++;
	}
}

void	move_z_decrease(t_dta **data)
{
	int i;

	i = 0;
	(*data)->angle.moves_count -= 0.03;
	while (i < (*data)->xyz.x * (*data)->xyz.y)
	{
		(*data)->pixel[i]->z = (*data)->angle.moves_count * (*data)->pixel[i]->z1;
		i++;
	}
}

int		key_hook(int key, t_dta *data)
{
	if (key == 53)
		exit(1); //need to clean everything before exit
	else if (key == 69 || key == 78)  //when plus on numpad is pressed, zoom in (+) image
		data->xyz.scale += (key == 69) ? 1 : -1;
	else if (key == 18) //press 1 to increase z
		move_z(&data);
	else if (key == 19) //press 2 to decrease z
		move_z_decrease(&data);
	else if (key == 126 || key == 125) //press up (on the arrows) to move image upper
		data->mlx.mv_y += (key == 126) ? -5 : 5;
	else if (key == 123 || key == 124)
		data->mlx.mv_x += (key == 123) ? -5 : 5;
	else if (key == 13 || key == 1) //w
		data->angle.x -= (key == 13) ? 0.01 : -0.01;
	else if (key == 0 || key == 2) //a 
		data->angle.y -= (key == 0) ? 0.01 : -0.01;
	else if (key == 25 || key == 29) // to rotate press 9 or 0 by z axis
		data->angle.z += (key == 25) ? 0.01 : -0.01; //9
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
	data = (t_dta *)malloc(sizeof(t_dta));
	angle.x = 0;
	angle.y = 0;
	angle.z = 0;
	mlx.mv_x = 0;
	mlx.mv_y = 0;
	angle.moves_count = 1;
	xyz.scale = scale(pixel, xyz, angle);
	data = (t_dta*)malloc(sizeof(t_dta));
	printf("zoom is calculeted\n");
	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, 1920, 1080, "FDF");
	draw_horizontal(pixel, xyz, mlx, angle);
	data->pixel = pixel;
	data->mlx = mlx;
	data->xyz = xyz;
	data->angle = angle;


	mlx_hook(mlx.window, 2, 0, (int (*)())key_hook, data);
	mlx_loop(mlx.ptr);
	return (0);
}
