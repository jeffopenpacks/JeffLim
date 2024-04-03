/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:10:56 by joolim            #+#    #+#             */
/*   Updated: 2024/02/24 12:05:34 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	change_colour(t_param *param, int keycode)
{
	if (keycode == 93)
	{
		if (param->option < 3)
			param->option += 1;
		else
			param->option = 1;
	}
	if (keycode == 91)
	{
		if (param->option > 1)
			param->option -= 1;
		else
			param->option = 3;
	}
	colour_code(param);
}

static int	key_hook(int keycode, t_param *param)
{
	if (keycode == 65307)
	{
		destroy_all(param);
		exit(0);
	}
	else if (keycode == 65361 || keycode == 97)
		param->x_mv -= 0.03;
	else if (keycode == 65362 || keycode == 119)
		param->y_mv -= 0.03;
	else if (keycode == 65363 || keycode == 100)
		param->x_mv += 0.03;
	else if (keycode == 65364 || keycode == 115)
		param->y_mv += 0.03;
	else if (keycode == 65451)
		param->max_iter += 5;
	else if (keycode == 65453)
	{
		if (param->max_iter > 50)
			param->max_iter -= 5;
	}
	else if (keycode == 91 || keycode == 93)
		change_colour(param, keycode);
	put_img(param);
	return (0);
}

static int	mse_scr(int button, int x, int y, t_param *param)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		param->zoom /= 1.1;
		if (param->max_iter < 1000)
			param->max_iter += 1;
	}
	else if (button == 5)
	{
		param->zoom *= 1.1;
		if (param->max_iter > 50)
			param->max_iter -= 1;
	}
	put_img(param);
	return (0);
}

static int	close_button(t_param *param)
{
	destroy_all(param);
	exit (0);
	return (0);
}

void	init_hooks(t_param *param)
{
	void	*w;

	w = param->win_ptr;
	mlx_key_hook(param->win_ptr, key_hook, param);
	mlx_mouse_hook(w, mse_scr, param);
	mlx_hook(param->win_ptr, 17, 0, close_button, param);
}
