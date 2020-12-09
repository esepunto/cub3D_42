/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/09 13:51:12 by ssacrist         ###   ########.fr       */
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
	a->rayc.dirplyr = 0.0;
	a->rayc.rush = 0.3;
	a->rayc.rotspeed = 0.3;
	a->rayc.lasttime = 0;
	a->rayc.delta = 1;
	a->rayc.xdist2coord = 0;
	a->rayc.ydist2coord = 0;
	a->rayc.fov = 60 * M_PI / 180;
	a->rayc.xray = 0;
	a->rayc.yray = 0;
	a->rayc.anglray = 0;
	a->rayc.quadrant = 0;
	a->rayc.xincrease = 0;
	a->rayc.yincrease = 0;
	a->rayc.xdist2coord = 0;
	a->rayc.ydist2coord = 0;
	a->rayc.distance = 0;
	a->rayc.initwall = 0;
	a->rayc.endwall = 0;
	a->rayc.staturewall = 0;
	a->rayc.nbr_ray = 0;
	a->rayc.xhit = 0;
	a->rayc.yhit = 0;
	a->rayc.wallcolor = 0;
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
