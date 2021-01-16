/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:25:55 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/12 00:47:47 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		msg_err(char *error)
{
	ft_printf("Error\n%s\n\n", error);
	system("leaks cub3D");
	exit(0);
}

void	delmem(t_cub3d *a)
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
