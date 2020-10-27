/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:05:36 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 11:17:39 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

#ifndef _UNISTD_H
# define _UNISTD_H

/*
** Shows the mouse.
**
** @return int has no return value (bc).
*/
int     mlx_mouse_show();

/*
** Moves the cursor to the given location.
**
** @param  void *win_ptr the window instance;
** @param  int  x        the x location to move to;
** @param  int  y        the y location to move to;
** @return int           has no return value (bc).
*/
int     mlx_mouse_move(void *win_ptr, int x, int y);

/*
** Gets the current mouse position on the window.
**
** @param  void *win_ptr the window instance;
** @param  int  *x       the pointer to write the x location to;
** @param  int  *y       the pointer to write the y location to;
** @return int           has no return value (bc).
*/
int     mlx_mouse_get_pos(void *win_ptr, int *x, int *y);

typedef struct  s_vars {
    void	*mlx;
    void	*win;
}               t_vars;

void	ft_putchars(int c)
{
	write(1, &c, 1);
}

void	ft_putnbrs(int nb)
{
	unsigned int	copy_nb;

	copy_nb = nb;
	if (copy_nb > 9)
		ft_putnbrs(copy_nb / 10);
	ft_putchars(copy_nb % 10 + '0');
}

void	ft_putstrs(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putchars(*str);
		str++;
	}
}

int		put_key(int keycode, t_vars *vars)
{
	if (keycode == 126)
		ft_putstrs("arriba");
	else if (keycode == 125)
		ft_putstrs("abajo");
	else if (keycode == 123)
		ft_putstrs("izquierda");
	else if (keycode == 124)
		ft_putstrs("derecha");
	else ft_putnbrs(keycode);
	ft_putchars(' ');
	ft_putchars('-');
	ft_putchars(' ');
	return (0);
}

int		close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int		get_mouse_action_and_position(int button, int x, int y, void *param)
{
	if (button == 1)
		ft_putstrs("click izquierdo en pos");
	else if (button == 2)
		ft_putstrs("clic derecho en pos");
	else if (button == 3)
		ft_putstrs("clic rueda en pos");
	else if (button == 5)
		ft_putstrs("rueda parriba en pos");
	else if (button == 4)
		ft_putstrs("rueda pabajo en pos");
	ft_putchars(' ');
	ft_putnbrs(x);
	ft_putchars(',');
	ft_putnbrs(y);
	ft_putchars(' ');
	ft_putchars('-');
	ft_putchars('\n');
	return (1);
}

/*
int		get_mouse_pos(int x, int y, void *param)//No funcona aun
{
//	mlx_mouse_get_pos;
	ft_putnbrs(x);
	ft_putchars(',');
	ft_putnbrs(y);
	ft_putchars(' ');
	ft_putchars('-');
	ft_putchars('\n');
	return (1);
}
*/

typedef struct  s_mouse_pos
{
    void	*win_ptr;
    int		*x;
	int		*y;
}               t_mouse_pos;

int		main(void)
{
	t_vars		vars;
	t_mouse_pos	mouse;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 480, "Buenorra, ese vinito blanco YAAAAAA!");
	mlx_mouse_move(vars.win, 25, 250);// OK
	mlx_mouse_hook(vars.win, &get_mouse_action_and_position, &vars);// OK
	mlx_mouse_hook(vars.win, &get_mouse_pos, &vars);//OK
	mlx_key_hook(vars.win, put_key, &vars);// OK
	mlx_key_hook(vars.win, close, &vars);// OK
	printf("%p", (int (*)(void *, int *, int *))mlx_mouse_get_pos);
	mlx_loop(vars.mlx);
}

#endif
