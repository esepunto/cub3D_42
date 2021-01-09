/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/09 06:16:09 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	init_struct(t_cub3d *a)
{
//	a->rayc.modulo = 0.00001;// El modulo se adapta a la resolución para hacer más eficiente el pintado
	a->rayc.modulo = (a->fconf.xrendersize
		* a->fconf.yrendersize) * 0.000000001;
	a->rayc.rush = 0.25;
	a->rayc.rotspeed = 0.10;
	a->rayc.fov = 66 * M_PI / 180;//Quizás debería vincularse tb a la resolución
//	a->rayc.fov = 180 / (a->fconf.xrendersize / a->fconf.yrendersize) * M_PI / 180;//Quizás debería vincularse tb a la resolución
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
