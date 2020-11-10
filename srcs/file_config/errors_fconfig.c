/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_fconfig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:57:34 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/10 23:36:37 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Check if anything param is repeat ("NO", "SO", etc.)
*/

void	is_repeat(int m, t_cub3d *a, const char *id)
{
	int			j;
	int			z;
	int			len;

	len = ft_strlen(id);
	m = m + 1;
	while (m < a->fconf.map.row)
	{
		j = jump_sp(m, 0, a);
		z = 0;
		while (z < len && a->fconf.map.map[m][j] == id[z])
		{
			if (z == len - 1)
			{
				if (a->fconf.final_line_params < m)
					a->fconf.final_line_params = m;
				msg_err("No no no no: a param is repeat.");
			}
			z++;
			j++;
		}
		m++;
	}
	return ;
}
