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

#include "fdf.h"
#include <stdio.h>

int		key_exit(int key, void *init)
{
//	(void)init;
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
	struct pixel_data	xyz;
	struct s_mlx		mlx;
	int					fd;
	char				*line;

	xyz.x = 0;
	xyz.y = 0;
	xyz.z = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	pixel = (t_pixel*)malloc(sizeof(t_pixel));
	ptr_pxl = pixel;
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
		while (*line != '\0')
		{
			pixel->z = ft_atoi(line);
			while (*line >= '0' && *line <= '9')
				line++;
			while (*line == ' ')
				line++;
			pixel->x = xyz.x;
			pixel->y = xyz.y;
			xyz.x++;
			pixel = pixel->next;
			pixel = (t_pixel*)malloc(sizeof(t_pixel));
		}
		xyz.y++;
		xyz.x = 0;
	}
	free(pixel);
	pixel = NULL;
	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, 1280, 720, "XYEBOE_OKHO");
	
	mlx_key_hook(mlx.window, key_exit, mlx.ptr);
	mlx_loop(mlx.ptr);
	return (0);
}
