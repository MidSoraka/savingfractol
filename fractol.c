/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:14:24 by vlaine            #+#    #+#             */
/*   Updated: 2022/05/25 11:27:07 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int mandelbrot_fractal(t_coords *coords)
{
	int count;
	long double tempx;

	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	while ((coords->zx * coords->zx + coords->zy * coords->zy < 4) && (count < coords->prm->iterations))
	{
		tempx = coords->zx * coords->zx - coords->zy * coords->zy + coords->cx;
		coords->zy = 2 * coords->zx * coords->zy + coords->cy;
		coords->zx = tempx;
		count++;
	}
	return (count);
}

static int julia_fractal(t_coords *coords)
{
	int count;
	long double tempx;

	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	while ((coords->zx * coords->zx + coords->zy * coords->zy < 4) && (count < coords->prm->iterations))
	{
		tempx = coords->zx * coords->zx - coords->zy * coords->zy + -0.7 * (0.7885) * (coords->prm->xside * (M_PI * 2));
		coords->zy = 2 * coords->zx * coords->zy + -0.7 * (0.7885) * (coords->prm->yside * (M_PI * 2));
		coords->zx = tempx;
		count++;
	}
	return (count);
}
// + 0.7885 * 2.71828 powf((0.7885 * 2.71828), (coords->prm->xside * 6.28318530718));
/* + powf(0.7885 * 2.71828, count * (coords->prm->xside * M_PI));
static int julia_fractal(t_coords *coords)
{
	int count;
	long double tempx;

	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	while ((coords->zx * coords->zx + coords->zy * coords->zy < 4) && (count < coords->prm->iterations))
	{
		tempx = coords->zx * coords->zx - coords->zy * coords->zy + -0.7 * (0.7885 * powf(2.71828, count * (coords->prm->xside * M_PI)));
		coords->zy = 2 * coords->zx * coords->zy + -0.7 * (0.7885 * powf(2.71828, count * (coords->prm->xside * M_PI)));
		coords->zx = tempx;
		count++;
	}
	return (count);
}
static int julia_fractal(t_coords *coords)
{
	int count;
	long double tempx;

	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	while ((coords->zx * coords->zx + coords->zy * coords->zy < 4) && (count < coords->prm->iterations))
	{
		tempx = coords->zx * coords->zx - coords->zy * coords->zy + (-0.7 * (coords->prm->xside * 6.28318530718));
		coords->zy = 2 * coords->zx * coords->zy * (coords->prm->xside * 6.28318530718);
		coords->zx = tempx;
		count++;
	}
	return (count);
}
static int julia_fractal(t_coords *coords)
{
	int count;
	long double tempx;
	long double n;

	count = 0;
	coords->zx = coords->cx;
	coords->zy = coords->cy;
	n = coords->prm->xside;
	while (count < coords->prm->iterations)
	{
		tempx = powf((coords->zx * coords->zx) + (coords->zy * coords->zy), (n / 2)) * cosf(n * atan2f(coords->zy, coords->zx)) + coords->cx;
		coords->zy = powf(((coords->zx * coords->zx) + (coords->zy * coords->zy)), n / 2) * sinf(n * atan2f(coords->zy, coords->zx)) + coords->cy;
		coords->zx = tempx;
		if ((coords->zx * coords->zx + coords->zy * coords->zy) > 4)
			break;
		count++;
	}
	return (count);
}*/

static int my_fractal(t_coords *coords)
{
	int count;

	count = 0;
	while (count < coords->prm->iterations)
	{
		coords->zx = coords->cx;
		coords->zy = coords->cy;
		
		coords->cx = coords->zx * coords->zx - coords->zy * coords->zy - 1;
		coords->cy = coords->zy * coords->zy - coords->zx * coords->zx - 1;
		
		if ((coords->cx * coords->cx + coords->cy * coords->cy) > 4)
			break;
		count++;
	}
	return (count);
}

static void *fractall(void *ptr)
{
	t_fractal *fractal;
	t_prm *prm;

	fractal = (t_fractal *) ptr;
	prm = fractal->prm;

	long double xscale, yscale;
	t_coords test;
	t_coords *coords;
    int maxx, maxy, count;
	int tempy, x, y;
	long double height;
	int	image_size;

	
	coords = &test;
	coords->prm = prm;
    maxx = prm->win_size[X];
    maxy = prm->win_size[Y];
    xscale = prm->decimal / (maxx + prm->scaleint);
    yscale = prm->decimal / (maxy + prm->scaleint);
	y = fractal->y;
	tempy = y + (prm->win_size[Y]/6);
	while (y < prm->win_size[Y] && y < tempy)
	{
		x = 0;
		while (x < prm->win_size[X])
		{
            coords->cx = (x * xscale) + prm->left;
            coords->cy = (y * yscale) + prm->top;
            count = (*fractal->ptr)(coords);
			height = (long double)count / prm->iterations; 
			image_size = (prm->mlx->size_line / 4) * (y + prm->loc[Y]) + (x + prm->loc[X]);
			if (count != prm->iterations)
				((unsigned int *)prm->mlx->image_add)[image_size] = (int)(height * INT_MAX) & (0xFFFFFF);
			else
				((unsigned int *)prm->mlx->image_add)[image_size] = (int)(0 * INT_MAX) & (0xFFFFFF);
			x++;
		}
		y++;
	}
	return(NULL);
}

void	fractol(t_prm *prm)
{
	t_fractal fractal[6];
	int (*ptr)(t_coords*);
	int index;
	int rc;
	void *ptr1;
	pthread_t *tid;
	int number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
	
	index = 0;
	mlx_mouse_get_pos(prm->mlx->win_ptr, &(prm->current_mouse_loc[X]), &(prm->current_mouse_loc[Y]));
	if (prm->bcommand == TRUE)
	{
		if (prm->current_mouse_loc[X] > prm->win_size[X])
			prm->current_mouse_loc[X] = prm->win_size[X];
		if (prm->current_mouse_loc[X] < 0)
			prm->current_mouse_loc[X] = 0;
		if (prm->current_mouse_loc[Y] > prm->win_size[Y])
			prm->current_mouse_loc[Y] = prm->win_size[Y];
		if (prm->current_mouse_loc[Y] < 0)
			prm->current_mouse_loc[Y] = 0;
		prm->xside = (long double)prm->current_mouse_loc[X]/prm->win_size[X];
		prm->yside = (long double)prm->current_mouse_loc[Y]/prm->win_size[Y];
	}
	prm->last_mouse_loc[X] = prm->current_mouse_loc[X];
	prm->last_mouse_loc[Y] = prm->current_mouse_loc[Y];
	if (ft_strcmp(prm->fractol_name, "julia") == 0)
		ptr = julia_fractal;
	else if (ft_strcmp(prm->fractol_name, "mandelbrot") == 0)
		ptr = mandelbrot_fractal;
	else if (ft_strcmp(prm->fractol_name, "my") == 0)
		ptr = my_fractal;
	tid = malloc(sizeof(pthread_t) * number_of_processors);
	while (index < number_of_processors)
	{
		fractal[index].ptr = ptr;
		fractal[index].prm = prm;
		fractal[index].y = index * (prm->win_size[Y]/number_of_processors);
		ptr1 = (void *)(&fractal[index]);
		rc = pthread_create(&tid[index], NULL, fractall, (void *)ptr1);
		if (rc)
		{
			ft_putendl("error, unable to create thread");
			exit(0);
		}
		index++;
	}
	index = 0;
	while (index < number_of_processors)
		pthread_join(tid[index++], NULL);
	free(tid);
}

/*
static int julia_fractal(float zx, float coords->zy, float coords->cx, float coords->cy, float xside)
{
	int count;

	count = 0;
	while (count < 50)
	{
		zx = coords->cx;
		coords->zy = cy;
		coords->cx = zx * zx - coords->zy * coords->zy + (-0.7);
		cy = 2 * zx * coords->zy + (0.27015);
		if ((coords->cx * coords->cx + coords->cy * coords->cy) > 4)
			break;
		count++;
	}
	return (count);
}
*/