/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/17 14:03:41 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  To check enough space to map: blank line after params, etc.
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
	frsline = a->fconf.map.first_line;
	if (ft_strlen(map[endline + 1]) > 1)
		msg_err("I need a blank line before params");
	if (row - endline <= 4)// <=4 if need a blank line after params, <=3 instead.
		msg_err("The map needs 3 rows at least");
	frsline = endline + 2;
	while (ft_strlen(map[frsline]) == 1)
	{
		frsline++;
		if (frsline == row)
			msg_err("The map needs to be in this universe.");
	}
	a->fconf.map.first_line = frsline;
}

/*
**  This function checks forbidden chars on first/end's line of the map.
*/

void	check_line_map(int line, t_cub3d *a)
{
	int		i;
	size_t	j;

	j = 0;
	if (line == a->fconf.map.row)
		i = line - 1;
	else
		i = line;
	while (j < ft_strlen(a->fconf.map.map[i]))
	{
		if (a->fconf.map.map[i][j] != '1'
				&& a->fconf.map.map[i][j] != ' '
				&& a->fconf.map.map[i][j] != '\0')
		{
			msg_err("Invalid chars at the top/end line.");
		}
		j++;
	}
}

/*
**  This function checks forbidden chars on first column of the map.
**  Remenber that i put a blank space at the end of all rows.
*/

void	check_frst_column(t_cub3d *a)
{
	char	**map;
	char	c;
	int		i;
	int		j;

	map = a->fconf.map.map;
	i = a->fconf.map.first_line;
	while (i < a->fconf.map.row)
	{
		j = 0;
		c = map[i][j];
		while (c == ' ')
		{
			j++;
			c = map[i][j];
		}
		if (c != '1' && c != '\0')
			msg_err("Have tou see first columns of map?");
		i++;
	}
}

void	find_map(t_cub3d *a)
{
	is_space2map(a);
//	check_line_map(a->fconf.map.row, a);
//	check_line_map(a->fconf.map.first_line, a);
	check_frst_column(a);
	review_map_horiz(a);
	map_open_algorithm(a);
}
