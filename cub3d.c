/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/01 20:24:36 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_struct(t_cub3d *a)
{
	int	c;

	c = 0;
	while (c <= 8)
	{
		a->fconf.wall_texture[c] = NULL;
		c++;
	}
	a->fconf.map.maze = NULL;
	a->fconf.map.row = 0;
	a->fconf.map.col = 0;
	a->fconf.final_line_params = 0;
	a->fconf.nb_wrd_param = 0;
	a->fconf.map.num_players = 0;
	a->rayc.xpos = 0.0;
	a->rayc.ypos = 0.0;
	a->rayc.plyr = ' ';
	
	a->rayc.xdir = 0;//Depends of player (N,S,WE,EA)
	a->rayc.ydir = 0;//Depends of player (N,S,WE,EA)
	a->rayc.xplane = 0;
	a->rayc.yplane = 0.66;
	a->rayc.time = 0;//time of current frame
	a->rayc.oldtime = 0;//time of previous frame
	a->rayc.movespeed = 1;
	a->rayc.rotspeed = 0.5;
	
	a->steal.modulo = 0.05;
	a->steal.dirplyr = 0.0;
	a->steal.movspeed = 0.5;
	a->steal.rotspeed = 0.5;
	a->steal.lasttime = 0;
	a->steal.delta = 0.5;
	
	

	
}

/*
**  line 40: to check if structs saved the data
*/

int		main(int argc, char **argv)
{
	t_cub3d	*a;

	if (argc == 2)
	{
		if (ft_chekext(argv[1], ".cub") != 0)
			msg_err("This is not a .cub file, bro.");
		a = (t_cub3d *)malloc(sizeof(t_cub3d));
		init_struct(a);
		open_fconfig(argv[1], a);
		init_window(a);
		delmem(a);
	}
	else
		msg_err("Revier your fingers, please.");
	system("leaks cub3D");
}
