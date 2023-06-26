/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:35:23 by okraus            #+#    #+#             */
/*   Updated: 2023/06/26 17:44:38 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

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
