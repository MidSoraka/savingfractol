/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:15:27 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/24 10:42:27 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h" //remove
#include "fractol.h"

int	main(int argc, char **argv)
{
	t_prm	prm;
	t_mlx	mlx;

	ft_bzero(&prm, sizeof(t_prm));
	ft_bzero(&mlx, sizeof(t_mlx));
	prm.mlx = &mlx;
	handle_file(argv[1], argc, &prm);
	open_window(&prm);
	return (0);
}
