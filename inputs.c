/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:54:18 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/25 09:23:23 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_input(int key, int x, int y, void *ptr)
{
	t_prm	*prm;
	t_mlx	*mlx;

	prm = ((t_prm *)ptr);
	mlx = prm->mlx;
	/*
	 + on zoom goes further while - goes closer
	 + on mouse position goes left while - goes right
	 + is down and - is up
	 prm->left += (((prm->decimal + (prm->decimal / (50 + prm->scaleint)))/(50 + prm->scaleint)) * 50);
	*/
	prm = ((t_prm *)ptr);
	mlx_mouse_get_pos(prm->mlx->win_ptr, &x, &y);
	prm->mouse_loc[X] = x;
	prm->mouse_loc[Y] = y;
	prm->left += (((prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint))) / (prm->win_size[X] + prm->scaleint)) * prm->mouse_loc[X]); // first calculates the new angle and then divides it by current and += it to the current one. Could Just calculate the new number, without dividing and then just set the new number to it.
	prm->top += (((prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint))) / (prm->win_size[Y] + prm->scaleint)) * prm->mouse_loc[Y]);
	if (key == MOUSE_SCROLL_DOWN && prm->scaleint > 1)
		prm->scaleint *= 0.5;
	if (key == MOUSE_SCROLL_UP && prm->scaleint < 13397580530642169204.0)
		prm->scaleint *= 1.5;
	prm->left -= (((prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint))) / (prm->win_size[X] + prm->scaleint)) * prm->mouse_loc[X]);
	prm->top -= (((prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint))) / (prm->win_size[Y] + prm->scaleint)) * prm->mouse_loc[Y]);
	return (0);
}

int	keyboard_input(int key, void *ptr)
{
	t_prm	*prm;
	t_mlx	*mlx;

	prm = ((t_prm *)ptr);
	mlx = prm->mlx;
	if (key == KEY_COMMAND)
	{
		if (prm->bcommand == TRUE)
			prm->bcommand = FALSE;
		else
			prm->bcommand = TRUE;
	}
	if (key == 53)
		exit_program(NULL, FALSE);
	if (key == KEY_ONE)
		prm->xside += 0.05;
	if (key == KEY_TWO)
		prm->xside -= 0.05;
	if (key == KEY_THREE)
		prm->yside += 0.05;
	if (key == KEY_FOUR)
		prm->yside -= 0.05;
	if (key == KEY_RIGHT)
		prm->left += (((prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint)))/(prm->win_size[X] + prm->scaleint)) * 50);
	if (key == KEY_LEFT)
		prm->left -= (((prm->decimal + (prm->decimal / (prm->win_size[X] + prm->scaleint)))/(prm->win_size[X] + prm->scaleint)) * 50);
	if (key == KEY_UP)
		prm->top -= (((prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint)))/(prm->win_size[Y] + prm->scaleint)) * 50);
	if (key == KEY_DOWN)
		prm->top += (((prm->decimal + (prm->decimal / (prm->win_size[Y] + prm->scaleint)))/(prm->win_size[Y] + prm->scaleint)) * 50);
	if (key == KEY_I && prm->iterations <= 1000)
		prm->iterations += 10;
	if (key == KEY_O && prm->iterations > 10)
		prm->iterations -= 10;
	if (key == KEY_PLUS) // remove
		prm->scaleint *= 1.5;
	printf("Scale is %Lf\n", prm->scaleint);
	printf("xside is %Lf\n", prm->xside);
	printf("yside is %Lf\n\n", prm->yside);
	return (0);
}

/*
if (key == MOUSE_SCROLL_DOWN)
	{
		prm->left += (((1.0 + (1.0 / (prm->win_size[X] + prm->scaleint)))/(prm->win_size[X] + prm->scaleint)) * prm->mouse_loc[X]);
		prm->top += (((1.0 + (1.0 / (prm->win_size[Y] + prm->scaleint)))/(prm->win_size[Y] + prm->scaleint)) * prm->mouse_loc[Y]);
		prm->scaleint *= 0.5;
		prm->left -= (((1.0 + (1.0 / (prm->win_size[X] + prm->scaleint)))/(prm->win_size[X] + prm->scaleint)) * prm->mouse_loc[X]);
		prm->top -= (((1.0 + (1.0 / (prm->win_size[Y] + prm->scaleint)))/(prm->win_size[Y] + prm->scaleint)) * prm->mouse_loc[Y]);
	}
	if (key == MOUSE_SCROLL_UP)
	{
		prm->left += (((1.0 + (1.0 / (prm->win_size[X] + prm->scaleint)))/(prm->win_size[X] + prm->scaleint)) * prm->mouse_loc[X]);
		prm->top += (((1.0 + (1.0 / (prm->win_size[Y] + prm->scaleint)))/(prm->win_size[Y] + prm->scaleint)) * prm->mouse_loc[Y]);
		//prm->scaleint += 5000;
		prm->scaleint *= 1.5;
		prm->left -= (((1.0 + (1.0 / (prm->win_size[X] + prm->scaleint)))/(prm->win_size[X] + prm->scaleint)) * prm->mouse_loc[X]);
		prm->top -= (((1.0 + (1.0 / (prm->win_size[Y] + prm->scaleint)))/(prm->win_size[Y] + prm->scaleint)) * prm->mouse_loc[Y]);
	}
*/
