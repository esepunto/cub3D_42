/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:10:39 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/25 13:57:28 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		closed(t_cub3d *a)
{
	mlx_destroy_window(a->mlibx.mlx, a->mlibx.win);
	system("leaks cub3D");
	exit(0);
}

/*
** Move forward if no wall in front of you
*/

void	go_front(t_cub3d *a)
{
//	if (a->fconf.map.maze[(int)(a->rayc.xpos + a->rayc.xdir * a->rayc.movespeed)][(int)(a->rayc.ypos)] == false)
	if (!(a->fconf.map.maze[(int)(a->rayc.xpos + a->rayc.xdir * a->rayc.movespeed)][(int)(a->rayc.ypos)]))
		a->rayc.xpos += a->rayc.xdir * a->rayc.movespeed;
//	if (a->fconf.map.maze[(int)(a->rayc.xpos)][(int)(a->rayc.ypos + a->rayc.ydir * a->rayc.movespeed)] == false)
	if (!(a->fconf.map.maze[(int)(a->rayc.xpos)][(int)(a->rayc.ypos + a->rayc.ydir * a->rayc.movespeed)]))
		a->rayc.ypos += a->rayc.ydir * a->rayc.movespeed;
}

/*
** Move backwards if no wall behind you
*/

void	go_back(t_cub3d *a)
{
//	if(a->fconf.map.maze[(int)(a->rayc.xpos - a->rayc.xdir * a->rayc.movespeed)][(int)(a->rayc.ypos)] == false)
	if(!(a->fconf.map.maze[(int)(a->rayc.xpos - a->rayc.xdir * a->rayc.movespeed)][(int)(a->rayc.ypos)]))
		a->rayc.xpos -= a->rayc.xdir * a->rayc.movespeed;
//	if(a->fconf.map.maze[(int)(a->rayc.xpos)][(int)(a->rayc.ypos - a->rayc.ydir * a->rayc.movespeed)] == false)
	if(!(a->fconf.map.maze[(int)(a->rayc.xpos)][(int)(a->rayc.ypos - a->rayc.ydir * a->rayc.movespeed)]))
		a->rayc.ypos -= a->rayc.ydir * a->rayc.movespeed;
}

void	go_left(t_cub3d *a)
{
	char	nada;
	nada = a->rayc.plyr;
}

void	go_right(t_cub3d *a)
{
	char	nada;
	nada = a->rayc.plyr;
}

/*
** Rotate to the right.
** Both camera direction and camera plane must be rotated.
*/

void	rotate_right(t_cub3d *a)
{
	a->rayc.xolddir = a->rayc.xdir;
	a->rayc.xdir = a->rayc.xdir * cos(-a->rayc.rootspeed) - a->rayc.ydir * sin(-a->rayc.rootspeed);
	a->rayc.ydir = a->rayc.xolddir * sin(-a->rayc.rootspeed) + a->rayc.ydir * cos(-a->rayc.rootspeed);
	a->rayc.xoldplane = a->rayc.xplane;
	a->rayc.xplane = a->rayc.xplane * cos(-a->rayc.rootspeed) - a->rayc.yplane * sin(-a->rayc.rootspeed);
	a->rayc.yplane = a->rayc.xoldplane * sin(-a->rayc.rootspeed) + a->rayc.yplane * cos(-a->rayc.rootspeed);
}

/*
** Rotate to the left.
** Both camera direction and camera plane must be rotated.
*/

void	rotate_left(t_cub3d *a)
{
	a->rayc.xolddir = a->rayc.xdir;
	a->rayc.xdir = a->rayc.xdir * cos(a->rayc.rootspeed) - a->rayc.ydir * sin(a->rayc.rootspeed);
	a->rayc.ydir = a->rayc.xolddir * sin(a->rayc.rootspeed) + a->rayc.ydir * cos(a->rayc.rootspeed);
	a->rayc.xoldplane = a->rayc.xplane;
	a->rayc.xplane = a->rayc.xplane * cos(a->rayc.rootspeed) - a->rayc.yplane * sin(a->rayc.rootspeed);
	a->rayc.yplane = a->rayc.xoldplane * sin(a->rayc.rootspeed) + a->rayc.yplane * cos(a->rayc.rootspeed);
}
