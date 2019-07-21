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
	t_pixel				*pixel;
	t_pixel				*ptr_pxl;
	struct s_size		size;
	t_pixel_data		xyz;
	t_mlx				mlx;
	int					fd;

	size.height = 0;
	size.width = 0;
	xyz.x = 0;
	xyz.y = 0;
	xyz.z = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	pixel = (t_pixel*)malloc(sizeof(t_pixel));
	ptr_pxl = pixel;
	get_pixels(fd, &xyz, &pixel);

	xyz.x = xyz.x / 2;
	xyz.y = xyz.y / 2;
	free(pixel);
	pixel = NULL;

	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, 1920, 1080, "XYEBOE_OKHO");
	//mlx.ptr_image = mlx_new_image(mlx.ptr, 720, 540);
	//mlx_put_image_to_window(mlx.ptr, mlx.window, mlx.ptr_image, 0, 0);
	mlx_pixel_put(mlx.ptr, mlx.window, 960 - xyz.x, 540 - xyz.y, 0xFF0000);
	mlx_key_hook(mlx.window, key_exit, mlx.ptr);
	mlx_loop(mlx.ptr);
	return (0);
}
