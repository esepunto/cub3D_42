/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:45:47 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/04 13:01:02 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	gofront(t_cub3d *a)
{
	a->steal.xplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	a->steal.yplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
	{
		a->steal.xplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	}
}

void	goback(t_cub3d *a)
{
	a->steal.xplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	a->steal.yplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
	{
		a->steal.xplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	}
}

void	goright(t_cub3d *a)
{
	a->steal.xplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	a->steal.yplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
	{
		a->steal.xplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	}
}

void	goleft(t_cub3d *a)
{
	a->steal.xplyr -= sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	a->steal.yplyr -= cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	if (a->fconf.map.maze[(int)a->steal.yplyr][(int)a->steal.xplyr] == '1')
	{
		a->steal.xplyr += sin(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
		a->steal.yplyr += cos(a->steal.dirplyr) * a->steal.movspeed * a->steal.delta;
	}
}

int		caress_key(int keycode, t_cub3d *a)
{
	a->rayc.keycode = keycode;
	if (a->rayc.keycode == KEY_ESC)
		closed(a);
	else if (a->rayc.keycode == KEY_MOVE_FRONT)
		gofront(a);
	else if (a->rayc.keycode == KEY_MOVE_BACK)
		goback(a);
	else if (a->rayc.keycode == KEY_MOVE_RIGHT)
		goright(a);
	else if (a->rayc.keycode == KEY_MOVE_LEFT)
		goleft(a);
	else if (a->rayc.keycode == KEY_LOOK_LEFT)
		a->steal.dirplyr -= a->steal.rotspeed * a->steal.delta;
	else if (a->rayc.keycode == KEY_LOOK_RIGHT)
		a->steal.dirplyr += a->steal.rotspeed * a->steal.delta;
	draw(a);
	return (0);
}
