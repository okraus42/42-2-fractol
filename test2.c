/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/05/20 14:30:49 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

/*
typedef enum scroll_keys
{
	MLX_ZOOM_IN		= 4,
	MLX_ZOOM_OUT	= 5,
}	scroll_key_t

bool mlx_is_scroll_in(mlx_t* mlx, scroll_key_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}

bool mlx_is_scroll_out(mlx_t* mlx, scroll_key_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}
*/
// -----------------------------------------------------------------------------

// struct s_colour
// {
// 	unsigned char	alpha;
// 	unsigned char	blue;
// 	unsigned char	green;
// 	unsigned char	red;
// }	t_colour;
typedef struct data_x
{
	int			x;
	int			y;
	int			z;
	long double	x0;
	long double	y0;
	long double	l;
	long double	xy[2];
} data_t;

typedef struct max_s
{
	mlx_t*		mlx;
	data_t*  	data;
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

/*int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}*/

void ft_colourize(void* param)
{
	union u_colour	test;

	test.rgbai = 0x00000000;
	test.srgba.blue = 0xff;
	test.srgba.alpha = 0xff;

	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		//test.srgba.blue -= 16;
		test.srgba.green += 8;
		test.srgba.red = 0;
		for (uint32_t y = 0; y < image->height; ++y)
		{
			test.srgba.red += 4;
			//test.srgba.green += 2;
			uint32_t colour = /*ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);*/
			colour = test.rgbai;
			mlx_put_pixel(image, i, y, colour);
		}
	}
}
void zoom(double xdelta, double ydelta, void* param)
{
	max_t*	max;
	long double	len;

	max = param;
	len = max->data->l;
	mlx_get_mouse_pos(max->mlx, &(max->data->x), &(max->data->y));
	/*if (ydelta < 0)
		*(int *)param = -1;
	if (ydelta > 0)
		*(int *)param = 1;
	if (xdelta < 0)
		*(int *)param = -1;
	if (xdelta > 0)
		*(int *)param = 1;*/
	if (ydelta < 0 && max->data->z > 1 && max->data->x >=0 && max->data->x <= 511
		&& max->data->y >=0 && max->data->y <= 511)
	{
		max->data->z -= 1;
		max->data->l *= 1.25;
	}
	if (ydelta > 0 && max->data->z < 256 && max->data->x >=0 && max->data->x <= 511
		&& max->data->y >=0 && max->data->y <= 511)
	{
		max->data->z += 1;
		max->data->l *= 0.8;
	}
	if (xdelta < 0)
		max->data->z += 0;
	//if (xdelta > 0)
	//	max->data->z += 1;
	//printf("B: %p | %d\n", param, *(int *)param);
	
	//max->data->l = 0.0078125 / max->data->z;
	max->data->x0 = max->data->x0 + max->data->x * len - max->data->x * max->data->l;
	max->data->y0 = max->data->y0 + max->data->y * len - max->data->y * max->data->l;

}

void ft_colourize2(void* max2)
{
	union u_colour	test;
	int32_t	x;
	int32_t	y;
	int32_t	z;
	max_t*	max;

	max = max2;
	test.rgbai = 0x00000000;
	test.srgba.alpha = 0xff;
	//printf("A1: %p | %d\n", &(max->data->z), max->data->z);
	z = max->data->z;
	mlx_get_mouse_pos(max->mlx, &x, &y);
	//usleep(10);
	//printf("A2: %p | %d\n", &(max->data->z), max->data->z);
	test.srgba.green = 0x7f;
	if (x >=0 && x <= 511 && y >=0 && y <= 511)
	{
		test.srgba.blue = (x / 2) % 256;
		test.srgba.red = (y / 2) % 256;
		test.srgba.green += z;
	}
	for (uint32_t i = 0; i < image->width; ++i)
	{
		//test.srgba.blue -= 16;
		for (uint32_t j = 0; j < image->height; ++j)
		{
			//test.srgba.green += 2;
			uint32_t colour = test.rgbai;
			mlx_put_pixel(image, i, j, colour);
		}
	}
}

int ft_iter(long double xy[2])
{
	int			iter;
	long double	x;
	long double	y;
	long double	x2;
	long double	y2;

	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0; 
	iter = 0;
	while (iter < 4096 && x + y <= 4)
	{
		y = 2 * x * y + xy[1];
		x = x2 - y2 + xy[0];
		x2 = x * x;
		y2 = y * y;
		iter++;
	}
	return (iter);
}

void ft_colourize3(void* max2)
{
	union u_colour	test;
	int32_t	x;
	int32_t	y;
	int32_t	z;
	int32_t	iter;
	max_t*	max;

	max = max2;
	test.rgbai = 0x00000000;
	test.srgba.alpha = 0xff;
	x = -1;
	y = -1;
	//printf("A1: %p | %d\n", &(max->data->z), max->data->z);

	z = max->data->z;
		
	//printf("%d\n", z);
	//max->data->l = 0.0078125;
	
	//usleep(10);
	//printf("A2: %p | %d\n", &(max->data->z), max->data->z);

	for (uint32_t i = 0; i < image->width; ++i)
	{
		//test.srgba.blue -= 16;
		for (uint32_t j = 0; j < image->height; ++j)
		{
			max->data->xy[0] = max->data->x0 + (max->data->l * i);
			max->data->xy[1] = max->data->y0 + (max->data->l * j);
			//printf("%10Lf\n", max->data->l);
			//printf("%Lf, %Lf\n", max->data->xy[0], max->data->xy[1]);
			iter = ft_iter(max->data->xy);
			test.srgba.blue = (iter * 0xf0) % 256;
			test.srgba.red = iter % 256;
			test.srgba.green = iter / 0xf0;
			uint32_t colour = test.rgbai;
			mlx_put_pixel(image, i, j, colour);
		}
	}
}

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[out] x The position.
 * @param[out] y The position.

void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);
 */

/**
 * This function sets the scroll callback, which is called when a scrolling 
 * device is used, such as a mouse wheel.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The scroll wheel callback function.
 * @param[in] param An additional optional parameter.

void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);
*/

/**
 * Callback function used to handle scrolling.
 * 
 * @param[in] xdelta The mouse x delta.
 * @param[in] ydelta The mouse y delta.
 * @param[in] param Additional parameter to pass on to the function.

typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);

*/

void ft_hook(void* param)
{
	max_t*	max;

	max = param;

	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(max->mlx);
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP))
		max->data->y0 -= max->data->l * 64;
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
		max->data->y0 += max->data->l * 64;
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
		max->data->x0 -= max->data->l * 64;
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
		max->data->x0 += max->data->l * 64;


}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;
	data_t	datat;
	max_t	maxt;
	data_t*	data;
	max_t*	max;

	data = &datat;
	max = &maxt;
	data->x = 0;
	data->y = 0;
	data->z = 1;
	data->l = 0.0078125;
	data->x0 = -2;
	data->y0 = -2;
	max->data = data;
	(void)argc;
	(void)argv;
	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	max->mlx = mlx;
	if (!(image = mlx_new_image(mlx, 511, 511)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	printf("%i", max->data->z);
	mlx_scroll_hook(mlx, &zoom, max);
	//mlx_loop_hook(mlx, ft_colourize, mlx);
	//mlx_loop_hook(mlx, ft_colourize2, max);
	max->data->xy[0] = -2;
	max->data->xy[1] = -2;
	mlx_loop_hook(mlx, ft_colourize3, max);
	mlx_loop_hook(mlx, ft_hook, max);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
