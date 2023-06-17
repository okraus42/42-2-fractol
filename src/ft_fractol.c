/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/17 16:55:27 by okraus           ###   ########.fr       */
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
int	ft_iter_1(t_max *max)
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
int	ft_iter_2(t_max *max)
{
	int			iter;
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;

	zx = max->data->zxy[0];
	zy = max->data->zxy[1];
	cx = max->data->cxy[0];
	cy = max->data->cxy[1];
	iter = 0;
	while (iter < max->data->iter && ((zx * zx) + (zy * zy)) < 4)
	{
		max->data->temp = (zx * zx) - (zy * zy);
		zy = 2 * (zx * zy) + cy;
		zx = max->data->temp + cx;
		iter++;
	}
	return (iter);
}

//Multibrot
int	ft_iter_3(t_max *max)
{
	int			iter;
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;

	zx = max->data->zxy[0];
	zy = max->data->zxy[1];
	cx = max->data->zxy[0];
	cy = max->data->zxy[1];
	iter = 0;
	while (iter < max->data->iter && ((zx * zx) + (zy * zy)) < 4)
	{
		max->data->temp = powl((zx * zx) + (zy * zy), (max->data->power / 2))
			* cosl(max->data->power * atan2l(zy, zx)) + cx;
		zy = powl(((zx * zx) + (zy * zy)), (max->data->power / 2))
			* sinl(max->data->power * atan2l(zy, zx)) + cy;
		zx = max->data->temp;
		iter++;
	}
	return (iter);
}

int	ft_iter(t_max *max)
{
	if (max->data->t == 1)
		return (ft_iter_1(max));
	else if (max->data->t > 1 && max->data->t < 7)
		return (ft_iter_2(max));
	else
		return (ft_iter_3(max));
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
			iter = ft_iter(max);
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
	max->data->cxy[0] = max->data->tmp[0] * cosl(max->data->alpha)
		- max->data->tmp[1] * sinl(max->data->alpha);
	max->data->cxy[1] = max->data->tmp[1]
		* cosl(max->data->alpha) + max->data->tmp[0] * sinl(max->data->alpha);
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
		if (max->data->afract < 67108864)
			max->data->afract *= 2;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_MULTIPLY))
	{
		if (max->data->power < 100)
			max->data->power += 0.015625;
		if (max->data->afract > 256)
			max->data->afract /= 2;
	}
}

void	ft_hook3(t_max *max)
{
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_8))
	{
		if (max->data->iter < 2048)
			max->data->iter *= 2;
	}
	if (mlx_is_key_down(max->mlx, MLX_KEY_KP_2))
	{
		if (max->data->iter > 8)
			max->data->iter /= 16;
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

void	ft_init_2(t_data *data)
{
	if (data->t > 1)
		data->iter = 256;
	if (data->t == 3)
	{
		data->cxy[0] = -0.8;
		data->cxy[1] = 0.156;
	}
	if (data->t == 4)
		data->cxy[1] = 0.8;
	if (data->t == 5)
	{
		data->cxy[0] = 0.285;
		data->cxy[1] = 0.01;
	}
	if (data->t == 6)
	{
		data->cxy[0] = 0.45;
		data->cxy[1] = 0.1428;
	}
}

void	ft_init_3(t_data *data)
{
	if (data->t == 7)
		data->power = 3;
	if (data->t == 8)
		data->power = 5;
	if (data->t == 9)
		data->power = 50;
	if (data->t > 6)
		data->iter = 32;
}

void	ft_init(t_data *data, int i)
{
	data->x = 0;
	data->y = 0;
	data->z = 1;
	data->iter = 1024;
	data->c = 0;
	data->power = 2;
	data->l = 0.0078125;
	data->x0 = -2;
	data->y0 = -2;
	data->amag = 0;
	data->alp = M_PI / 65536;
	data->afract = 65536;
	data->alpha = data->alp * data->amag;
	data->temp2 = 0;
	data->cxy[0] = -0.4;
	data->cxy[1] = 0.6;
	data->temp = 0;
	data->zxy[0] = -2;
	data->zxy[1] = -2;
	data->t = i;
	ft_init_2(data);
	ft_init_3(data);
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

void	ft_errormsg(int n)
{
	if (n == 1)
		ft_printf_fd(2, "%61CIncorrect number of arguments%0C\n");
	if (n == 2)
		ft_printf_fd(2, "%64CIncorrect argument%0C\n");
	ft_printf_fd(2, "%21CPlease use numbers 1 - 9 as arguments:%0C\n");
	ft_printf_fd(2, "%72C1%0C%32C - Mandelbrot%0C\n");
	ft_printf_fd(2, "%73C2%0C%33C - Julia c = -0.4 + 0.6i%0C\n");
	ft_printf_fd(2, "%73C3%0C%33C - Julia c = -0.8 + 0.156i%0C\n");
	ft_printf_fd(2, "%73C4%0C%33C - Julia c = 0.8i%0C\n");
	ft_printf_fd(2, "%73C5%0C%33C - Julia c = 0.285 + 0.01i%0C\n");
	ft_printf_fd(2, "%73C6%0C%33C - Julia c = 0.45 + 0.1428i%0C\n");
	ft_printf_fd(2, "%65C7%0C%25C - Multibrot n = 3%0C\n");
	ft_printf_fd(2, "%65C8%0C%25C - Multibrot n = 5%0C\n");
	ft_printf_fd(2, "%65C9%0C%25C - Multibrot n = 50%0C\n");
}

int	main(int argc, char *argv[])
{
	int		i;
	t_max	*max;

	if (argc != 2)
	{
		ft_errormsg(1);
		return (1);
	}
	i = ft_atoi(argv[1]);
	if (i < 1 || i > 10)
	{
		ft_errormsg(2);
		return (2);
	}
	max = NULL;
	return (ft_fractol(max, i));
}
