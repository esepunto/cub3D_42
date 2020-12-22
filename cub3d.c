/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/22 13:35:08 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_struct(t_cub3d *a)
{
	a->rayc.modulo = 0.0002;
	a->rayc.rush = 1.0;
	a->rayc.rotspeed = 0.3;
	a->rayc.delta = 0.15;
	a->rayc.fov = 60 * M_PI / 180;
}

int		main(int argc, char **argv)
{
	t_cub3d	*a;
	double x = 0.5;//
	double b;

	if (argc == 2)
	{
		b = asin(x);
		printf("arcsin (%f) = %f\n", x, b);
		printf("sin (%f) = %f\n", b, sin(b));
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
