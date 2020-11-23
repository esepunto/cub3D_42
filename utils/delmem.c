/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delmem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:25:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 11:27:16 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	delmem(t_cub3d *a)
{
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
