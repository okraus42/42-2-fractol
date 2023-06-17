/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/06/17 12:20:36 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

// INCLUDES

# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <sys/wait.h> //check if needed, but it must be
# include <time.h> //check if needed
# include <sys/types.h> //open function1
# include <sys/stat.h> //open function2
# include <fcntl.h> //open function3
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/header/libft.h"

// DEFINITIONS

// STRUCTURES
// FRACTOL structure

typedef struct data_s
{
	int			x;
	int			y;
	int			z;
	int			temp2;
	int			iter;
	int			c;
	int			t; //type of fractal 1-Mandelbrot, 2-Julia, 3-Multibrot
	long double	x0;
	long double	y0;
	long double	l;
	long double	alp;	//default alp
	long double	alpha; //final alpha
	int			amag; //magnitude of alpha
	int			afract;
	long double	power;
	long double	tmp[2];
	long double	zxy[2];
	long double	cxy[2];
	long double	temp;
} data_t;

typedef struct max_s
{
	mlx_t		*mlx;
	data_t		*data;
	mlx_image_t	*image;
} max_t;

union u_colour
{
	struct s_colour
	{
		unsigned char	alpha;
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
	}	srgba;
	int				rgbai;
}	u_rgba;

// PROTOTYPES

//	ft_draw

#endif
