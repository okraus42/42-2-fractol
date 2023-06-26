/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:43:01 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:45:19 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

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
