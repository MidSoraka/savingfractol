/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:16:34 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/24 10:38:53 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define INT_MAX 2147483647
# define X 0
# define Y 1
# define Z 2
# define KEY_X 7
# define KEY_C 8
# define KEY_R 15
# define KEY_Y 16
# define KEY_U 32
# define KEY_COMMAND 15
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_I 34
# define KEY_O 31
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_UP 126
# define KEY_DOWN 125
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE_BUTTON 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define BOOL int
# define TRUE 1
# define FALSE 0

# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "pthread.h"
# include "printf.h" //remove

typedef struct s_prm
{
	struct s_mlx		*mlx;
	char				*fractol_name;
	int					win_size[3];
	int					scale[3];
	int					loc[3];
	long double			scaleint;
	BOOL				bcommand;
	long double			decimal;
	int					mouse_loc[2];
	int					last_mouse_loc[2];
	int					current_mouse_loc[2];
	int					iterations;
	long double			left;
	long double			top;
	long double			xside;
	long double			yside;
	unsigned int		color;
}				t_prm;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image_ptr;
	char		*image_add;
	int			size_line;
	int			erdian;
	int			bpp;
}				t_mlx;

typedef struct s_coords
{
	long double	zx;
	long double	zy;
	long double	cx;
	long double	cy;
	t_prm		*prm;
}				t_coords;

typedef struct s_fractal
{
	t_prm	*prm;
	int		y;
	int		(*ptr)(t_coords*);
}				t_fractal;
void	exit_program(char *error_msg, BOOL berror);
void	handle_file(char *argv, int argc, t_prm *prm);
void	open_window(t_prm *prm);
int		keyboard_input(int key, void *ptr);
int		mlx_window_loop(void *ptr);
void	fractol(t_prm *prm);
int		mouse_input(int key, int x, int y, void *ptr);

#endif
