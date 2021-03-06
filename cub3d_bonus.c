/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/21 19:39:50 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d_bonus.h"

int			close_window(t_cub3d *a)
{
	mlx_destroy_window(a->mlibx.mlx, a->mlibx.win);
	system("leaks cub3D_bonus");
	exit(0);
}

int			msg_err(char *error)
{
	ft_printf("Error\n%s\n\n", error);
	system("leaks cub3D_bonus");
	exit(0);
}

void		calc_lifepoints(t_cub3d *a)
{
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '2')
		a->life -= 10;
	if (a->fconf.map.maze[(int)a->rayc.yplyr][(int)a->rayc.xplyr] == '3')
		a->life += 10;
}

/*
** Modulo is the length of the step on the ray during the raycast.
** The longer the modulo the faster the program and inferior image quality.
**
** Other options to calc modulo.
** a->rayc.modulo = a->fconf.xrendersize * a->fconf.yrendersize) * 0.000000001;
** a->rayc.modulo = 0.0003;
*/

static void	init_struct(t_cub3d *a)
{
	a->rayc.modulo =
		a->fconf.xrendersize * a->fconf.yrendersize * 0.0003 / 240000;
	a->rayc.rush = 0.2;
	a->rayc.rotspeed = 0.10;
	a->rayc.fov = 60 * M_PI / 180;
	a->life = 100;
}

/*
** I think the programs is close to absolut perfect.
** It's time to write the last comments.
*/

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
		msg_err("Review your fingers, please.");
}
