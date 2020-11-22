/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/22 20:38:10 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_struct(t_cub3d *a)
{
	a->fconf.map.map = NULL;
	a->fconf.map.row = 0;
	a->fconf.map.col = 0;
	a->fconf.final_line_params = 0;
	a->fconf.nb_wrd_param = 0;
}

/*
**  line 40: to check if structs saved the data
*/

int		main(int argc, char **argv)
{
	t_cub3d	*a;
	int		len;

	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		if (ft_chekext(argv[1], ".cub") != 0)
			msg_err("This is not a .cub file, bro.");
		a = (t_cub3d *)malloc(sizeof(t_cub3d));
		init_struct(a);
		open_fconfig(argv[1], a);
		if (a)
		{
			if (sizeof(a->fconf.wall_texture) >= 848)
				ft_delmatrix(a->fconf.wall_texture);
			if (sizeof(a->fconf.map.map) >= 208)
				ft_delmatrix(a->fconf.map.map);
			if (sizeof(a) >= sizeof(t_cub3d))
				free(a);
		}
	}
	else
		msg_err("Revier your fingers, please.");
	system("leaks cub3D");
}
