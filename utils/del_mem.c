/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:17:23 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/07 11:29:14 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	del_mem_fconf(t_cub3d *a)
{
	int		i;
	char *c;

	i = 0;
	while (i <= 7)
	{
//		ft_memdel((void **)a->fconf.wall_texture[i]);
		c = a->fconf.wall_texture[i];
		i++;
	}
}

void	del_mem(t_cub3d *a)
{
	del_mem_fconf(a);
}
