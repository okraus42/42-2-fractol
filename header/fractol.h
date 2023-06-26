/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:44:54 by okraus           ###   ########.fr       */
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

# define WIDTH 512
# define HEIGHT 512

// STRUCTURES
// FRACTOL structure

// typedef struct data_s
// {
// 	int			x;
// 	int			y;
// 	int			z;
// 	int			temp2;
// 	int			iter;
// 	int			c;
// 	int			t;		//type of fractal 1-Mandelbrot, 2-Julia, 3-Multibrot
// 	long double	x0;
// 	long double	y0;
// 	long double	l;
// 	long double	alp;	//default alp
// 	long double	alpha;	//final alpha
// 	int			amag;	//magnitude of alpha
// 	int			afract;
// 	long double	power;
// 	long double	tmp[2];
// 	long double	zxy[2];
// 	long double	cxy[2];
// 	long double	temp;
// }	t_data;

typedef struct data_s
{
	int			x;
	int			y;
	int			z;
	int			temp2;
	int			iter;
	int			c;
	int			t;
	long double	x0;
	long double	y0;
	long double	l;
	long double	alp;
	long double	alpha;
	int			amag;
	int			afract;
	long double	power;
	long double	tmp[2];
	long double	zxy[2];
	long double	cxy[2];
	long double	temp;
}	t_data;

typedef struct max_s
{
	mlx_t		*mlx;
	t_data		*data;
	mlx_image_t	*image;
}	t_max;

typedef union u_colour
{
	struct s_colour
	{
		unsigned char	alpha;
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
	}	srgba;
	int				rgbai;
}	t_rgba;

// PROTOTYPES

//	ft_draw
void	zoom(double xdelta, double ydelta, void *param);
//Mandelbrot
int		ft_iter_1(t_max *max);
//Julia
int		ft_iter_2(t_max *max);
//Multibrot
int		ft_iter_3(t_max *max);
int		ft_iter(t_max *max);

//	ft_colours
void	ft_colourize(void	*max2);

//	ft_hook
void	ft_hook(void *param);
void	ft_hook2(t_max *max);
void	ft_hook3(t_max *max);

//	ft_init
void	ft_init(t_data *data, int i);
void	ft_init_2(t_data *data);
void	ft_init_3(t_data *data);

#endif
