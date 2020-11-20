/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/20 09:20:04 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  To check that map exists and save the first line of map
*/

void	is_space2map(t_cub3d *a)
{
	char	**map;
	int		frsline;
	int		endline;
	int		row;

	map = a->fconf.map.map;
	row = a->fconf.map.row;
	endline = a->fconf.final_line_params;
	frsline = a->fconf.map.first_line;// ¿Por qué no puedo quitarla?
	frsline = endline + 1;
	while (ft_strlen(map[frsline]) == 1)
	{
		frsline++;
		if (frsline == row)
			msg_err("The map needs to be in this universe.");
	}
	a->fconf.map.first_line = frsline;
}

void	find_map(t_cub3d *a)
{
	is_space2map(a);
	review_map_horiz(a);
	map_algorithm(a);
}
