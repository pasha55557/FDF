/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:54:52 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/15 14:31:14 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	get_min_max_z(t_pixel_data *xyz, int z)
{
	if (z > xyz->max_z)
		xyz->max_z = z;
	if (z < xyz->min_z)
		xyz->min_z = z;
}

int		get_color_of_z(t_pixel_data *xyz, int z)
{
	int				red;
	int				green;
	int				blue;
	double			percentage;
	t_data_cords	cord;

	cord.start_c = 0xFFFFFF;
	cord.end_c = 0x0000FF;
	percentage = percent(xyz->min_z, xyz->max_z, z);
<<<<<<< HEAD
	red = get_light((cord.start_c >> 16) & 0xFF,
	(cord.end_c >> 16) & 0xFF, percentage);
	green = get_light((cord.start_c >> 8) & 0xFF,
	(cord.end_c >> 8) & 0xFF, percentage);
	blue = get_light(cord.start_c & 0xFF, cord.end_c & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
=======
    red = get_light((cord.start_c >> 16) & 0xFF, (cord.end_c >> 16) & 0xFF, percentage);
    green = get_light((cord.start_c >> 8) & 0xFF, (cord.end_c >> 8) & 0xFF, percentage);
    blue = get_light(cord.start_c & 0xFF, cord.end_c & 0xFF, percentage);
    return ((red << 16) | (green << 8) | blue);
}

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
		if (*hex >= 97 && *hex <= 102)
			tmp[1] = 87;
		if (*hex >= 65 && *hex <= 70)
			tmp[1] = 55;
		if (*hex >= '0' && *hex <= '9')
			tmp[1] = 48;
		tmp[0] = (*hex - tmp[1]) * pow(16, power);
		dec = dec + tmp[0];
		hex++;
		power--;
	}
	return(dec);
>>>>>>> 395ca133764f701a5892f94301f484461e09b46d
}

int		get_color(char *line)
{
	char	*ptr_color;
	int		int_color;
	char	*color;

	int_color = 0;
	color = ft_strnew(7);
	ptr_color = color;
	while (*line != 'x')
		line++;
	line++;
	while (!(ft_isspace(*line) || *line == '\0'))
	{
		*color = *line;
		color++;
		line++;
	}
	int_color = from_hex_to_dec(ptr_color);
	ft_strdel(&ptr_color);
	return (int_color);
}

void	move_line(t_pixel_data *xyz, t_pixel **pixel,
t_tmp *arg, char **line)
{
	if (ft_isdigit(**line))
	{
		pixel[arg->i]->z = ft_atoi(*line);
		pixel[arg->i]->z1 = pixel[arg->i]->z;
		pixel[arg->i]->x = xyz->x++;
		get_min_max_z(xyz, pixel[arg->i]->z);
		if (xyz->weight < xyz->x)
			xyz->weight = xyz->x;
		pixel[arg->i]->y = xyz->y;
		while (ft_isdigit(**line))
			(*line)++;
		if (arg->color_id == 1)
		{
			if (**line == ',')
			{
				pixel[arg->i]->color = get_color(*line);
				while (!(ft_isspace(**line) || **line == '\0'))
					(*line)++;
			}
			else
				pixel[arg->i]->color = 0xFFFFFF;
		}
		arg->i++;
	}
}

void	get_pixels(int fd, t_pixel_data *xyz, t_pixel **pixel)
{
	char				*line;
	char				*ptr_line;
	t_tmp				arg;

	arg.color_id = pixel[0]->color;
	arg.i = 0;
	xyz->y = 0;
	while (get_next_line(fd, &line) == 1)
	{
		ptr_line = line;
		xyz->weight = 0;
		xyz->x = 0;
		while (*line != '\0')
		{
<<<<<<< HEAD
			move_line(xyz, pixel, &arg, &line);
=======
			if (ft_isdigit(*line))
			{
				//printf("%d   %d\n", xyz->x, xyz->y);
				pixel[i]->z = ft_atoi(line);
				pixel[i]->z1 = pixel[i]->z;
				pixel[i]->x = xyz->x;
				xyz->x++;
				get_min_max_z(xyz, pixel[i]->z);
				if (xyz->weight < xyz->x)
					xyz->weight = xyz->x;
				pixel[i]->y = xyz->y;				
				while (ft_isdigit(*line))
				line++;
				if (color_id == 1)
				{
					if (*line == ',')
					{
						pixel[i]->color = get_color(line);
						while (!(ft_isspace(*line) || *line == '\0'))
							line++;
					}
					else
						pixel[i]->color = 0xFFFFFF;
				}
				i++;
			}
>>>>>>> 395ca133764f701a5892f94301f484461e09b46d
			while (ft_isspace(*line))
				line++;
		}
		xyz->y++;
		ft_strdel(&ptr_line);
	}
	ft_strdel(&ptr_line);
	if (arg.color_id == 0)
		while (--arg.i >= 0)
			pixel[arg.i]->color = get_color_of_z(xyz, pixel[arg.i]->z);
}
