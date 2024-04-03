/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:23:05 by joolim            #+#    #+#             */
/*   Updated: 2024/02/24 11:56:56 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	render_img(t_param *param)
{
	param->img.img_ptr = mlx_new_image(param->mlx_ptr, WIDTH, HEIGHT);
	if (!(param->img.img_ptr))
	{
		mlx_destroy_window(param->mlx_ptr, param->win_ptr);
		free(param->mlx_ptr);
		error_exit("Failed to init img");
	}
	param->img.data = mlx_get_data_addr(param->img.img_ptr, &(param->img.bpp),
			&(param->img.size), &(param->img.endian));
}

static void	data_init(t_param *param)
{
	param->zoom = 1.0;
	param->max_iter = 50;
	param->x_mv = 0.0;
	param->y_mv = 0.0;
	param->julia_c.real = 0.0;
	param->julia_c.imag = 0.0;
	param->profile[0] = 4;
	param->profile[1] = 2;
	param->profile[2] = 1;
	param->option = 1;
}

static void	init_param(t_param *param)
{
	param->mlx_ptr = mlx_init();
	if (!(param->mlx_ptr))
		error_exit("Failed to init mlx");
	param->win_ptr = mlx_new_window(param->mlx_ptr, WIDTH,
			HEIGHT, param->name);
	if (!param->win_ptr)
	{
		free(param->mlx_ptr);
		error_exit("Failed to init window");
	}
	data_init(param);
	init_hooks(param);
}

int	main(int argc, char **argv)
{
	t_param	param;

	if ((argc == 2 && !(ft_strncmp(argv[1], "mandelbrot", 10))) || \
			(argc == 4 && !(ft_strncmp(argv[1], "julia", 5))))
	{
		param.name = argv[1];
		init_param(&param);
		if (argc == 4)
		{
			param.julia_c.real = ft_atod(argv[2]);
			param.julia_c.imag = ft_atod(argv[3]);
		}
		render_img(&param);
		put_img(&param);
		mlx_loop(param.mlx_ptr);
	}
	else
		error_exit("Enter <Mandelbrot> or <julia>,  <value1>, <value2>");
	return (0);
}
