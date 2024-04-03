/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:40:11 by joolim            #+#    #+#             */
/*   Updated: 2024/02/17 13:12:57 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	map_colour(int value, t_param *param)
{
	int	r;
	int	g;
	int	b;

	if (value == param->max_iter)
		return (0);
	r = (255 * param->profile[0] * value) / param->max_iter;
	g = (255 * param->profile[1] * value) / param->max_iter;
	b = (255 * param->profile[2] * value) / param->max_iter;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 125;
	if (b > 255)
		b = 60;
	if (value < param->max_iter / 3)
		return ((r << 16) | (g << 8) | b);
	if (value < 2 * param->max_iter / 3)
		return ((g << 16 | (b << 8) | r));
	else
		return ((b << 16 | (r << 8) | g));
}

void	colour_code(t_param *param)
{
	if (param->option == 1)
	{
		param->profile[0] = 2;
		param->profile[1] = 4;
		param->profile[2] = 8;
	}
	if (param->option == 2)
	{
		param->profile[0] = 4;
		param->profile[1] = 8;
		param->profile[2] = 2;
	}
	if (param->option == 3)
	{
		param->profile[0] = 8;
		param->profile[1] = 4;
		param->profile[2] = 2;
	}
}

double	ft_atod(char *str)
{
	int		intvalue;
	double	result;
	char	*dp;
	double	fraction;

	intvalue = ft_atoi(str);
	if (intvalue < 0)
		intvalue *= -1;
	result = (double)intvalue;
	fraction = 0.1;
	dp = ft_strchr(str, '.');
	if (dp)
		dp++;
	while ((dp) && *dp >= '0' && *dp <= '9')
	{
		result += (*dp - '0') * fraction;
		fraction /= 10.0;
		dp++;
	}
	if (*str == '-')
		result *= -1;
	return (result);
}

void	destroy_all(t_param *param)
{
	mlx_destroy_image(param->mlx_ptr, param->img.img_ptr);
	mlx_destroy_window(param->mlx_ptr, param->win_ptr);
	mlx_destroy_display(param->mlx_ptr);
	free(param->mlx_ptr);
	exit(EXIT_SUCCESS);
}

void	error_exit(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}
