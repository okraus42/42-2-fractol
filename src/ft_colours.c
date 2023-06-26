/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colours.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:43:12 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:44:07 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

static void	ft_colourize2(t_max	*max, t_rgba test)
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
