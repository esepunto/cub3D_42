/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:17:23 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/16 17:59:19 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	del_mem_fconf(t_cub3d *a)
{
	int		i;

	i = 0;

	while (i < a->fconf.map.row)
	{
		if (a->fconf.map.map[i])
		{
			free(a->fconf.map.map[i]);
			a->fconf.map.map[i] = NULL;
		}
		i++;
	}
}

void	del_mem(t_cub3d *a)
{
	del_mem_fconf(a);
	if (a)
	{
		free(a);
		a = NULL;
	}
}
