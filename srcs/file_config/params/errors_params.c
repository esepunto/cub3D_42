/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:57:34 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/18 10:25:59 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** Check if anything param is repeat ("NO", "SO", etc.)
*/

void	is_repeat(int thisline, t_cub3d *a, const char *id)
{
	int			j;
	int			z;
	int			len;

	len = ft_strlen(id);
	thisline = thisline + 1;
	while (thisline < a->fconf.map.row)
	{
		j = jump_sp(thisline, a);
		z = 0;
		while (z < len && a->fconf.map.map[thisline][j] == id[z])
		{
			if (z == len - 1)
			{
				if (a->fconf.final_line_params < thisline)
					a->fconf.final_line_params = thisline;
				msg_err("No no no no: a param is repeat.");
			}
			z++;
			j++;
		}
		thisline++;
	}
	return ;
}
