/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:54:52 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/23 18:57:00 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		from_HEX_to_DEC(char *hex)
{
	int	tmp[2];
	int	dec;
	int power;

	dec = 0;
	power = strlen(hex);
	power--;
	while (power != -1)
	{
		if (*hex >= 65 && *hex <= 70)
			tmp[1] = 55;
		if (*hex >= '0' && *hex <= '9')
			tmp[1] = *hex;
		//tmp[0] = (*hex - tmp[1]);
		tmp[0] = (*hex - tmp[1]) * pow(16, power);
		dec = dec + tmp[0];
		hex++;
		power--;
	}
	return(dec);
}

int		get_color(char *line)
{
	char	*ptr_color;
	int		int_color;
	char 	*color;

	int_color = 0;
	color = ft_strnew(7);
	ptr_color = color;
	while (*line != 'x')
	line++;
	line++;
	while (*line != ' ')
	{
		*color = *line;
		color++;
		line++;
	}
	int_color = from_HEX_to_DEC(ptr_color);
	free(ptr_color);
	return(int_color);
}

int		get_pixels(int fd, t_pixel_data *xyz, t_pixel **pixel)
{
	char				*line;
	char				*ptr_line;

	while (get_next_line(fd, &line) == 1)
	{
		ptr_line = line;
		xyz->x = 0;
		printf("%s\n", ptr_line);
		while (*ptr_line != '\0')
		{
			(*pixel)->z = ft_atoi(ptr_line);
			while (*ptr_line >= '0' && *ptr_line <= '9')
				ptr_line++;
				if (*ptr_line == ',')
				{
					(*pixel)->color = get_color(ptr_line);
					ptr_line++;
				}
				else
					(*pixel)->color = 16777215;
			while (*ptr_line == ' ')
				ptr_line++;
			(*pixel)->x = xyz->x;
			(*pixel)->y = xyz->y;
			xyz->x++;
			(*pixel) = (*pixel)->next;
			(*pixel) = (t_pixel*)malloc(sizeof(t_pixel));
		}
		xyz->y++;
	}
	return (0);
}