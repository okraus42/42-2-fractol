/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:43:08 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:43:54 by okraus           ###   ########.fr       */
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
