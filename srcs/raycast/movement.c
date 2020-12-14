/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:45:47 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/14 13:38:12 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	gofront(t_cub3d *a)
{
	a->rayc.xplyr += cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	a->rayc.yplyr += sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1')
	{
		a->rayc.xplyr -= cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
		a->rayc.yplyr -= sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	}
}

void	goback(t_cub3d *a)
{
	a->rayc.xplyr -= cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	a->rayc.yplyr -= sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1')
	{
		a->rayc.xplyr += cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
		a->rayc.yplyr += sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	}
}

void	goright(t_cub3d *a)
{
	a->rayc.xplyr -= sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	a->rayc.yplyr += cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1')
	{
		a->rayc.xplyr += sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
		a->rayc.yplyr -= cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	}
}

void	goleft(t_cub3d *a)
{
	a->rayc.xplyr += sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	a->rayc.yplyr -= cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1')
	{
		a->rayc.xplyr -= sin(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
		a->rayc.yplyr += cos(a->rayc.dirplyr) * a->rayc.rush * a->rayc.delta;
	}
}

int		caress_key(int keycode, t_cub3d *a)
{
	a->rayc.keycode = keycode;
	if (a->rayc.keycode == KEY_ESC)
		close_window(a);
	else if (a->rayc.keycode == KEY_MOVE_FRONT)
		gofront(a);
	else if (a->rayc.keycode == KEY_MOVE_BACK)
		goback(a);
	else if (a->rayc.keycode == KEY_MOVE_RIGHT)
		goright(a);
	else if (a->rayc.keycode == KEY_MOVE_LEFT)
		goleft(a);
	else if (a->rayc.keycode == KEY_ROTATE_LEFT)
		a->rayc.dirplyr -= a->rayc.rotspeed * a->rayc.delta;
	else if (a->rayc.keycode == KEY_ROTATE_RIGHT)
		a->rayc.dirplyr += a->rayc.rotspeed * a->rayc.delta;
	throw_rays(a);
	return (0);
}
