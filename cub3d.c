/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 11:17:00 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"


void	init_struct(t_cub3d *a)
{
	a->fconf.map.map = NULL;
	a->fconf.map.row = 0;
	a->fconf.map.col = 0;
}

int		main(int argc, char **argv)
{
	t_cub3d	a;

	init_struct(&a);
	if (argc == 2)
	{
		read_fconfig(argv[1], &a);
		print_fconfig(&a);//To check if structs saved the data
	}
	else
		msg_err("Either U type what I need 2 read or our LV is impossible.\n");
	system("leaks cub3D");
}
