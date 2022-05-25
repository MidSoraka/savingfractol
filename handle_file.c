/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:20:29 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/24 10:39:18 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static BOOL	is_valid_fractal_name(char *str)
{
	if (ft_strcmp(str, "mandelbrot") == 0)
		return (TRUE);
	if (ft_strcmp(str, "julia") == 0)
		return (TRUE);
	if (ft_strcmp(str, "my") == 0)
		return (TRUE);
	return (FALSE);
}

void	handle_file(char *argv, int argc, t_prm *prm)
{
	if (argc != 2)
		exit_program("julia\nmandelbrot\nmy", TRUE);
	prm->fractol_name = &argv[0];
	if (!prm->fractol_name)
		exit_program("error", TRUE);
	if (is_valid_fractal_name(prm->fractol_name) == FALSE)
		exit_program("julia\nmandelbrot\nmy", TRUE);
}
