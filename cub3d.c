/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:17:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/06 14:27:57 by ssacrist         ###   ########.fr       */
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
	t_cub3d	*a;
	int		len;

//	init_struct(&a);
	if (argc == 2)
	{
		if (ft_memcmp(argv[0], "./cub3D", 7))
			msg_err("What're you doing? It isn't the executable file!");
		len = ft_strlen(argv[1]);
		if (ft_memcmp(argv[1] + len - 4, ".cub", 4))
			msg_err("This is not a .cub file, bro.");
		a = (t_cub3d *)malloc(sizeof(t_cub3d));
		init_struct(a);
		read_fconfig(argv[1], a);
		print_fconfig(a);//To check if structs saved the data

	}
	else
		msg_err("Either U type what I need 2 read or our LV is impossible.");
	system("leaks cub3D");
}
