/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/16 22:21:39 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int			msg_err(char *error)
{
	ft_printf("Error\n%s\n\n", error);
	system("leaks cub3D");
	exit(0);
}

void		delmem(t_cub3d *a)
{
	if (a)
	{
		if (sizeof(a->fconf.wall_texture) >= 848)
			ft_delmatrix(a->fconf.wall_texture);
		if (sizeof(a->fconf.wall) >= 848)
			ft_delmatrix(a->fconf.wall);
		if (sizeof(a->fconf.map.maze) >= 208)
			ft_delmatrix(a->fconf.map.maze);
		if (sizeof(a) >= sizeof(t_cub3d))
			free(a);
	}
}

static void	init_struct(t_cub3d *a)
{
	a->rayc.modulo = (a->fconf.xrendersize
		* a->fconf.yrendersize) * 0.000000001;
	a->rayc.rush = 0.10;
	a->rayc.rotspeed = 0.10;
	a->rayc.fov = 66 * M_PI / 180;
}

int			main(int argc, char **argv)
{
	t_cub3d	*a;

	if (argc == 2 || argc == 3)
	{
		if (!(a = ft_calloc(sizeof(a), sizeof(t_cub3d))))
			msg_err("WTF! Give me back my memory!");
		if (ft_chekext(argv[1], ".cub") != 0)
			msg_err("This is not a .cub file, bro.");
		if (argc == 3)
		{
			if (ft_checkwords(argv[2], "--save") != 0)
				msg_err("To save a -bmp screenshot, type --save.");
			a->save_bmp = true;
		}
		open_fconfig(argv[1], a);
		init_struct(a);
		init_window(a);
		delmem(a);
	}
	else
		msg_err("Revier your fingers, please.");
}
