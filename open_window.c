/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:45:37 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/24 10:42:52 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	default_fractal_settings(t_prm *prm)
{
	prm->bcommand = FALSE;
	prm->scaleint = 100;
	prm->xside = 1.0;
	prm->yside = prm->xside;
	prm->decimal = 5.0;
	prm->iterations = 50;
	prm->left = 0.0;
	prm->top = 0.0;
}

static void	default_window_settings(t_prm *prm)
{
	prm->win_size[X] = 1792;
	prm->win_size[Y] = 1280;
	ft_bzero(&prm->scale, sizeof(prm->scale)); // check that it reaches the Z value too
	ft_bzero(&prm->loc, sizeof(prm->loc));
}

void	open_window(t_prm *prm)
{
	t_mlx	*mlx;

	default_window_settings(prm);
	default_fractal_settings(prm);
	mlx = prm->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, prm->win_size[X], prm->win_size[Y], "win");
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, prm->win_size[X], prm->win_size[Y]);
	mlx->image_add = mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->size_line, &mlx->erdian);
	mlx_loop_hook(mlx->mlx_ptr, mlx_window_loop, prm);
	mlx_key_hook(mlx->win_ptr, keyboard_input, prm);
	mlx_mouse_hook(mlx->win_ptr, mouse_input, prm);
	mlx_loop(mlx->mlx_ptr);
}
