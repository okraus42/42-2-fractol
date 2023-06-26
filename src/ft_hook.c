/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:43:17 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:44:20 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

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
