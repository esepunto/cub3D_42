/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:14:28 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/13 10:14:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#ifndef _UNISTD_H
# define _UNISTD_H

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	unsigned int	copy_nb;

	copy_nb = nb;
	if (copy_nb > 9)
		ft_putnbr(copy_nb / 10);
	ft_putchar(copy_nb % 10 + '0');
}

typedef struct  s_program
{
    void *mlx;
    void *win;
}               t_program;

int mouse_event(int button, int x, int y, void *param)
{
    t_program *tutorial = param;
    
    mlx_pixel_put(tutorial->mlx, tutorial->win, 640/2, 360/2, 0xFFFFFF);
    mlx_mouse_get_pos(tutorial->win, &x, &y);
    ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar(',');
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putchar('-');
	ft_putchar('\n');
    return (1);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Event Parameters");

    t_program tutorial;
    tutorial.mlx = mlx;
    tutorial.win = win;

    mlx_mouse_hook(win, &mouse_event, &tutorial);

    mlx_loop(mlx);
}

#endif