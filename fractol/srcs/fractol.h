/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:33:01 by joolim            #+#    #+#             */
/*   Updated: 2024/02/16 12:45:26 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <math.h>

# define WIDTH 500
# define HEIGHT 500

typedef struct s_cplx{
	double	real;
	double	imag;
}	t_cplx;

typedef struct s_img{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size;
	int		endian;
}	t_img;

typedef struct s_fractal{
	char	*name;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		max_iter;
	int		profile[3];
	int		option;
	double	zoom;
	double	x_mv;
	double	y_mv;
	t_cplx	julia_c;
}	t_param;

int		main(int argc, char **argv);
double	ft_atod(char *str);
void	destroy_all(t_param *param);
void	error_exit(char *str);
void	put_img(t_param *param);
void	init_hooks(t_param *param);
void	colour_code(t_param *param);
int		map_colour(int value, t_param *param);

#endif
