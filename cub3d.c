/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/28 01:58:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	init_struct(t_cub3d *a)
{
	a->rayc.modulo = 0.0002;
	a->rayc.rush = 0.15;
	a->rayc.rotspeed = 0.03;
	a->rayc.fov = 60 * M_PI / 180;
}

int			main(int argc, char **argv)
{
	t_cub3d	*a;

	if (argc == 2)
	{
		if (ft_chekext(argv[1], ".cub") != 0)
			msg_err("This is not a .cub file, bro.");
		if (!(a = ft_calloc(sizeof(a), sizeof(t_cub3d))))
			msg_err("WTF! Give me back my memory!");
		init_struct(a);
		open_fconfig(argv[1], a);
		init_window(a);
		delmem(a);
	}
	else
		msg_err("Revier your fingers, please.");
	system("leaks cub3D");
}
