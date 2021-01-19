/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 07:00:31 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int			msg_err(char *error)
{
	ft_printf("Error\n%s\n\n", error);
	system("leaks cub3D");
	exit(0);
}

static void	init_struct(t_cub3d *a)
{
	a->rayc.modulo = (a->fconf.xrendersize
		* a->fconf.yrendersize) * 0.000000001;
	a->rayc.rush = 0.2;
	a->rayc.rotspeed = 0.10;
	a->rayc.fov = 66 * M_PI / 180;
	a->life = 100;
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
	}
	else
		msg_err("Revier your fingers, please.");
}
