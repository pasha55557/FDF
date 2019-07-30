/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:54:52 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/27 18:43:05 by rsticks          ###   ########.fr       */
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
	free(&ptr_color);
	return(int_color);
}

void		get_pixels(int fd, t_pixel_data *xyz, t_pixel **pixel)
{
	char				*line;
	char				*ptr_line;
	int					i;

	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		ptr_line = line;
		xyz->weight = 0;
		xyz->x = 0;
		//printf("%s\n", line);
		while (*line != '\0')
		{
			
			if (ft_isdigit(*line))
			{
				//printf("%d   %d\n", xyz->x, xyz->y);
				pixel[i]->z = ft_atoi(line);
				pixel[i]->x = xyz->x;
				xyz->x++;
				if (xyz->weight < xyz->x)
					xyz->weight = xyz->x;				
				while (ft_isdigit(*line))
				line++;
			}
			if (*line == ',')
			{
				pixel[i]->color = get_color(line);
				line = line + 9;
			}
			else
				pixel[i]->color = 16777215;
			while (ft_isspace(*line))
				line++;
			pixel[i]->y = xyz->y;
			i++;
		}
		xyz->y++;
	}
	ft_strdel(&ptr_line);
	//printf("x = %d, y = %d, z = %d", pixel[2 + 2 * xyz->weight]->x, pixel[2 + 2 * xyz->weight]->y, pixel[2 + 2 * xyz->weight]->z);
	//printf("maxx %d, maxy %d, maxz %d", xyz->x, xyz->y, xyz->z);
	//return (0);
}