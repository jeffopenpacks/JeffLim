/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:45:28 by joolim            #+#    #+#             */
/*   Updated: 2024/02/16 13:46:17 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_cplx	map(int x, int y, t_param *param)
{
	t_cplx	c;

	c.real = ((x - WIDTH / 2.0) / (WIDTH / 4.0) * param->zoom) + param->x_mv;
	c.imag = ((y - HEIGHT / 2.0) / (HEIGHT / 4.0) * param->zoom) + param->y_mv;
	return (c);
}

static int	mandelbrot(t_cplx z, t_cplx c, int max_iter)
{
	int		iter;
	double	temp;

	iter = 0;
	while (iter < max_iter && z.real * z.real + z.imag * z.imag < 4.0)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp;
		iter++;
	}
	return (iter);
}

static int	set_cplx(t_cplx *z, t_cplx *c, t_param *param)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp(param->name, "mandelbrot", 10))
	{
		z->real = 0.0;
		z->imag = 0.0;
		c->real = 0.0;
		c->imag = 0.0;
		flag = 0;
	}
	else
	{
		c = &(param->julia_c);
		flag = 1;
	}
	return (flag);
}

static void	find_value(int x, int y, t_param *param)
{
	t_cplx	z;
	t_cplx	c;
	char	*dest;
	int		colour;
	int		value;

	if (set_cplx(&z, &c, param) == 0)
		c = map(x, y, param);
	else
	{
		z = map(x, y, param);
		c = param->julia_c;
	}
	value = mandelbrot(z, c, param->max_iter);
	colour = map_colour(value, param);
	dest = param->img.data + (y * param->img.size + (x * param->img.bpp / 8));
	*(unsigned int *)dest = colour;
}

void	put_img(t_param *param)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	ft_bzero(param->img.data, param->img.size);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			find_value(x, y, param);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, \
			param->img.img_ptr, 0, 0);
}
