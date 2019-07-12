/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 14:53:18 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/12 16:07:26 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx_macos/mlx.h"
#include "fdf.h"
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"

typedef struct	s_pixel
{
	int			count;
	int			color;
	int			x;
	int			y;
	int			z;
	struct		s_pixel *next;
}				t_pixel;

struct pixel_data
{
	int	x;
	int	y;
	int z;
};


struct			s_mlx
{
	void		*ptr;
	void		*window;	
};
#endif