/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:45:47 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 19:13:35 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	gofront(t_cub3d *a)
{
	a->rayc.xplyr += cos(a->rayc.dirplyr) * a->rayc.rush;
	a->rayc.yplyr += sin(a->rayc.dirplyr) * a->rayc.rush;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1'
		|| a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '2')
	{
		a->rayc.xplyr -= cos(a->rayc.dirplyr) * a->rayc.rush;
		a->rayc.yplyr -= sin(a->rayc.dirplyr) * a->rayc.rush;
		a->life -= 10;
	}
}

static void	goback(t_cub3d *a)
{
	a->rayc.xplyr -= cos(a->rayc.dirplyr) * a->rayc.rush;
	a->rayc.yplyr -= sin(a->rayc.dirplyr) * a->rayc.rush;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1'
		|| a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '2')
	{
		a->rayc.xplyr += cos(a->rayc.dirplyr) * a->rayc.rush;
		a->rayc.yplyr += sin(a->rayc.dirplyr) * a->rayc.rush;
		a->life -= 10;
	}
}

static void	goright(t_cub3d *a)
{
	a->rayc.xplyr -= sin(a->rayc.dirplyr) * a->rayc.rush;
	a->rayc.yplyr += cos(a->rayc.dirplyr) * a->rayc.rush;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1'
		|| a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '2')
	{
		a->rayc.xplyr += sin(a->rayc.dirplyr) * a->rayc.rush;
		a->rayc.yplyr -= cos(a->rayc.dirplyr) * a->rayc.rush;
		a->life -= 10;
	}
}

static void	goleft(t_cub3d *a)
{
	a->rayc.xplyr += sin(a->rayc.dirplyr) * a->rayc.rush;
	a->rayc.yplyr -= cos(a->rayc.dirplyr) * a->rayc.rush;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '1'
		|| a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '2')
	{
		a->rayc.xplyr -= sin(a->rayc.dirplyr) * a->rayc.rush;
		a->rayc.yplyr += cos(a->rayc.dirplyr) * a->rayc.rush;
		a->life -= 10;
	}
}

int			caress_key(t_cub3d *a)
{
	if (a->rayc.keycode[KEY_ESC])
		close_window(a);
	if (a->rayc.keycode[KEY_MOVE_FRONT])
		gofront(a);
	if (a->rayc.keycode[KEY_MOVE_BACK])
		goback(a);
	if (a->rayc.keycode[KEY_MOVE_RIGHT])
		goright(a);
	if (a->rayc.keycode[KEY_MOVE_LEFT])
		goleft(a);
	if (a->rayc.keycode[KEY_ROTATE_RIGHT])
		a->rayc.dirplyr += a->rayc.rotspeed;
	if (a->rayc.keycode[KEY_ROTATE_LEFT])
		a->rayc.dirplyr -= a->rayc.rotspeed;
	a->rayc.dirplyr = fmod(a->rayc.dirplyr, M_PI * 2);
	throw_rays(a);
	return (0);
}
