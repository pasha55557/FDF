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

int		key_exit(int key, void *init)
{
	(void)init;
	if (key == 53)
	{
		exit(1);
	}
	return(0);
}

int		main(int argc, char **argv)
{
	t_pixel				**pixel;
	struct s_size		size;
	t_pixel_data		xyz;
	t_mlx				mlx;
	int					fd;
	int					zoom;


	size.height = 0;
	size.width = 0;
	xyz.x = 0;
	xyz.y = 0;
	xyz.z = 0;
	if (argc != 2)
	{
		ft_putendl("Валидация: пиздец, карты нет");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	pixel = init_pixel(fd);
	fd = open(argv[1], O_RDONLY);
	ft_putstr("file is open\n");
	get_pixels(fd, &xyz, pixel);
	printf("координаты записаны\n");
	xyz.scale = scale(pixel, xyz);
	printf("zoom is calculeted\n");
	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, 1920, 1080, "FDF");
	//draw_line(xyz, mlx);
	//draw_hor_line(pixel, xyz, mlx);
	draw_horizontal(pixel, xyz, mlx);
	//mlx.ptr_image = mlx_new_image(mlx.ptr, 720, 540);
	//mlx_put_image_to_window(mlx.ptr, mlx.window, mlx.ptr_image, 0, 0);
	//mlx_pixel_put(mlx.ptr, mlx.window, 960 - xyz.x, 540 - xyz.y, 0xFF0000);
	mlx_key_hook(mlx.window, key_exit, mlx.ptr);
	mlx_loop(mlx.ptr);
	return (0);
}
