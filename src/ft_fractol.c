/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/17 13:40:05 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

void	zoom(double xdelta, double ydelta, void *param)
{
	t_max		*max;
	long double	len;

	max = param;
	len = max->data->l;
	mlx_get_mouse_pos(max->mlx, &(max->data->x), &(max->data->y));
	if (ydelta < 0 && max->data->z > 1 && max->data->x >= 0
		&& max->data->x <= 511 && max->data->y >= 0 && max->data->y <= 511)
	{
		max->data->z -= 1;
		max->data->l *= 1.25;
	}
	if (ydelta > 0 && max->data->z < 256 && max->data->x >= 0
		&& max->data->x <= 511 && max->data->y >= 0 && max->data->y <= 511)
	{
		max->data->z += 1;
		max->data->l *= 0.8;
	}
	if (xdelta < 0)
		max->data->z += 0;
	max->data->x0 += max->data->x * len - max->data->x * max->data->l;
	max->data->y0 += max->data->y * len - max->data->y * max->data->l;
}

//Mandelbrot
int	ft_iter_1(t_max	*max)
{
	int			iter;
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;

	zx = 0;
	zy = 0;
	cx = 0;
	cy = 0;
	iter = 0;
	while (iter < max->data->iter && (cx + cy) <= 4)
	{
		zy = 2 * zx * zy + max->data->zxy[1];
		zx = cx - cy + max->data->zxy[0];
		cx = zx * zx;
		cy = zy * zy;
		iter++;
	}
	return (iter);
}

//Julia
int	ft_iter_2(t_max	*max)
{
	int			iter;
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;

	zx = 0;
	zy = 0;
	cx = 0;
	cy = 0;
	iter = 0;
	while (iter < max->data->iter && (cx + cy) <= 4)
	{
		zy = 2 * zx * zy + max->data->zxy[1];
		zx = cx - cy + max->data->zxy[0];
		cx = zx * zx;
		cy = zy * zy;
		iter++;
	}
	return (iter);
}

//Multibrot
int	ft_iter_3(t_max	*max)
{
	int			iter;
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;

	zx = 0;
	zy = 0;
	cx = 0;
	cy = 0;
	iter = 0;
	while (iter < max->data->iter && (cx + cy) <= 4)
	{
		zy = 2 * zx * zy + max->data->zxy[1];
		zx = cx - cy + max->data->zxy[0];
		cx = zx * zx;
		cy = zy * zy;
		iter++;
	}
	return (iter);
}

void	ft_colourize2(t_max	*max, t_rgba test)
{
	int				iter;
	int				c;
	unsigned int	i[2];

	i[0] = 0;
	while (i[0] < max->image->height)
	{
		i[1] = 0;
		while (i[1] < max->image->width)
		{
			max->data->zxy[0] = max->data->x0 + (max->data->l * i[1]);
			max->data->zxy[1] = max->data->y0 + (max->data->l * i[0]);
			iter = ft_iter_1(max);
			test.srgba.blue = ((max->data->c + iter) * 16) % 256;
			test.srgba.red = ((iter)) % 256;
			test.srgba.green = ((iter) / 4) % 256;
			if (iter == max->data->iter)
				test.rgbai = 0x000000ff;
			c = test.rgbai;
			mlx_put_pixel(max->image, i[1], i[0], c);
			i[1]++;
		}
		i[0]++;
	}
}

void	ft_colourize(void	*max2)
{
	t_rgba	test;
	t_max	*max;

	max = max2;
	test.rgbai = 0x00000000;
	test.srgba.alpha = 0xff;
	max->data->temp2++;
	max->data->alp = M_PI / max->data->afract;
	max->data->alpha = max->data->alp * max->data->amag;
	max->data->tmp[0] = max->data->cxy[0];
	max->data->tmp[1] = max->data->cxy[1];
	ft_colourize2(max, test);
}

void	ft_hook2(t_max *max)
{
	if (mlx_is_key_down(max->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(max->mlx);
	if (mlx_is_key_down(max->mlx, MLX_KEY_UP))
		max->data->y0 -= max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_DOWN))
		max->data->y0 += max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_LEFT))
		max->data->x0 -= max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_RIGHT))
		max->data->x0 += max->data->l * 16;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_DIVIDE))
	{
		if (max->data->power > 0.1)
			max->data->power -= 0.015625;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_MULTIPLY))
	{
		if (max->data->power < 100)
			max->data->power += 0.015625;
	}
}

void	ft_hook3(t_max *max)
{
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_8))
	{
		if (max->data->iter < 1024)
			max->data->iter += 16;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_2))
	{
		if (max->data->iter > 16)
			max->data->iter -= 16;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_4))
	{
		max->data->c--;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_6))
	{
		max->data->c++;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_ADD))
		max->data->amag = 1;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_0))
		max->data->amag = 0;
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_SUBTRACT))
		max->data->amag = -1;
}

void	ft_hook(void *param)
{
	t_max	*max;

	max = param;
	ft_hook2(max);
	ft_hook3(max);
}

// -----------------------------------------------------------------------------

void	ft_init(t_data	*data, int i)
{
	data->x = 0;
	data->y = 0;
	data->z = 1;
	data->iter = 2048;
	data->c = 0;
	data->power = 2;
	data->l = 0.0078125;
	data->x0 = -2;
	data->y0 = -2;
	data->amag = 0;
	data->alp = 0;
	data->afract = 1;
	data->alpha = data->alp * data->amag;
	data->temp2 = 0;
	data->cxy[0] = 0;
	data->cxy[1] = 0;
	data->temp = 0;
	data->zxy[0] = -2;
	data->zxy[1] = -2;
	data->t = i;
}

int	ft_fractol_2(t_max *max)
{
	if (!(max->image))
	{
		mlx_close_window(max->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(max->mlx, max->image, 0, 0) == -1)
	{
		mlx_close_window(max->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_scroll_hook(max->mlx, &zoom, max);
	mlx_loop_hook(max->mlx, ft_colourize, max);
	mlx_loop_hook(max->mlx, ft_hook, max);
	mlx_loop(max->mlx);
	mlx_terminate(max->mlx);
	return (EXIT_SUCCESS);
}

int	ft_fractol(t_max *max, int i)
{
	mlx_t		*mlx;
	t_data		datat;
	t_max		maxt;
	t_data		*data;
	mlx_image_t	*image;

	data = &datat;
	ft_init(data, i);
	max = &maxt;
	image = NULL;
	(void)i;
	max->image = image;
	max->data = data;
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	max->mlx = mlx;
	max->image = mlx_new_image(mlx, 511, 511);
	return (ft_fractol_2(max));
}

int	main(int argc, char *argv[])
{
	int		i;
	t_max	*max;

	(void)argc;
	(void)argv;
	i = 0;
	max = NULL;
	return (ft_fractol(max, i));
}
