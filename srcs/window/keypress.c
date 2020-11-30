/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:10:39 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/30 14:41:29 by ssacrist         ###   ########.fr       */
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
	if (a->fconf.map.maze[(int)(a->rayc.ypos + a->rayc.ydir * a->rayc.movespeed)][(int)(a->rayc.xpos)] != '1')
		a->rayc.xpos += a->rayc.xdir * a->rayc.movespeed;
	if (a->fconf.map.maze[(int)(a->rayc.ypos)][(int)(a->rayc.xpos + a->rayc.xdir * a->rayc.movespeed)] != '1')
		a->rayc.ypos += (a->rayc.ydir * a->rayc.movespeed);
}

/*
** Move backwards if no wall behind you
*/

void	go_back(t_cub3d *a)
{
	int xpos = (int)a->rayc.xpos;
	int ypos = (int)a->rayc.ypos;
	int xdir = (int)a->rayc.xdir;
	int ydir = (int)a->rayc.ydir;
	char **maze = a->fconf.map.maze;

	if (maze[ypos - ydir][xpos] != '1')
		xpos -= xdir;
	if (maze[ypos][xpos - xdir] != '1')
		a->rayc.ypos -= ydir;
		
/*	if (a->fconf.map.maze[(int)(a->rayc.ypos - a->rayc.ydir * a->rayc.movespeed)][(int)(a->rayc.xpos)] != '1')
		a->rayc.xpos -= a->rayc.xdir * a->rayc.movespeed;
	if (a->fconf.map.maze[(int)(a->rayc.ypos)][(int)(a->rayc.xpos - a->rayc.xdir * a->rayc.movespeed)] != '1')
		a->rayc.ypos -= (a->rayc.ydir * a->rayc.movespeed);*/
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

void	rotate_left(t_cub3d *a)
{
	a->rayc.xolddir = a->rayc.xdir;
	a->rayc.xdir = a->rayc.xdir * cos(- a->rayc.rotspeed) - a->rayc.ydir * sin(- a->rayc.rotspeed);
	a->rayc.ydir = a->rayc.xolddir * sin(- a->rayc.rotspeed) + a->rayc.ydir * cos(- a->rayc.rotspeed);
	a->rayc.xoldplane = a->rayc.xplane;
	a->rayc.xplane = a->rayc.xplane * cos(- a->rayc.rotspeed) - a->rayc.yplane * sin(- a->rayc.rotspeed);
	a->rayc.yplane = a->rayc.xoldplane * sin(- a->rayc.rotspeed) + a->rayc.yplane * cos(- a->rayc.rotspeed);
}

/*
** Rotate to the left.
** Both camera direction and camera plane must be rotated.
*/

void	rotate_right(t_cub3d *a)
{
	a->rayc.xolddir = a->rayc.xdir;
	a->rayc.xdir = a->rayc.xdir * cos(a->rayc.rotspeed) - a->rayc.ydir * sin(a->rayc.rotspeed);
	a->rayc.ydir = a->rayc.xolddir * sin(a->rayc.rotspeed) + a->rayc.ydir * cos(a->rayc.rotspeed);
	a->rayc.xoldplane = a->rayc.xplane;
	a->rayc.xplane = a->rayc.xplane * cos(a->rayc.rotspeed) - a->rayc.yplane * sin(a->rayc.rotspeed);
	a->rayc.yplane = a->rayc.xoldplane * sin(a->rayc.rotspeed) + a->rayc.yplane * cos(a->rayc.rotspeed);
}
