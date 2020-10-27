/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:14:28 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 11:11:50 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			ft_putchars(int c)
{
	write(1, &c, 1);
}

void			ft_putnbrs(int nb)
{
	unsigned int	copy_nb;

	copy_nb = nb;
	if (copy_nb > 9)
		ft_putnbrs(copy_nb / 10);
	ft_putchars(copy_nb % 10 + '0');
}

typedef struct	s_program
{
	void *mlx;
	void *win;
}				t_program;

int 			mouse_event(int x, int y, void *param)
{
	t_program *tutorial = param;

	mlx_pixel_put(tutorial->mlx, tutorial->win, 640/2, 360/2, 0xFFFFFF);
	mlx_mouse_get_pos(tutorial->win, &x, &y);
	ft_putchars(' ');
	ft_putnbrs(x);
	ft_putchars(',');
	ft_putnbrs(y);
	ft_putchars(' ');
	ft_putchars('-');
	ft_putchars('\n');
	return (1);
}

int				main()
{
	void		*mlx = mlx_init();
	void		*win = mlx_new_window(mlx, 640, 360, "Event Parameters");
	t_program	tutorial;

	tutorial.mlx = mlx;
	tutorial.win = win;
	mlx_mouse_hook(win, &mouse_event, &tutorial);
	mlx_loop(mlx);
}
