/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/20 13:27:47 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** Check if ther're chars forbidden on map.
** The map only accepts '0','1','2','N','S','E','W' and ' ' (space).
*/

void	forbidd_chr(char c)
{
	if (c != '0' && c != '1' && c != '2' && c != ' ' && c != 'N'
			&& c != 'S' && c != 'E' && c != 'W' && c != '\0')
	{
		msg_err("Forbidden characters in map");
	}
}

/*
**  It counts if there're more than one player.
*/

void	repeat_chr(int i, size_t j, t_cub3d *a)
{
	if (a->fconf.map.map[i][j] == 'N' || a->fconf.map.map[i][j] == 'S'
		|| a->fconf.map.map[i][j] == 'W' || a->fconf.map.map[i][j] == 'E')
	{
		a->fconf.map.num_players++;
	}
	if (a->fconf.map.num_players > 1)
		msg_err("Please, review the number of players.");
}

/*
**  This function checks forbidden/repeat chars
**  and if there's a player.
*/

void	review_map(t_cub3d *a)
{
	int		i;
	size_t	j;

	i = a->fconf.map.first_line;
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j < ft_strlen(a->fconf.map.map[i]))
		{
			if (ft_isprint(a->fconf.map.map[i][j]) == 1)
			{
				forbidd_chr(a->fconf.map.map[i][j]);
				repeat_chr(i, j, a);
			}
			j++;
		}
		i++;
	}
	if (a->fconf.map.num_players == 0)
		msg_err("Hey, the map can't run without player!");
}

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
	frsline = endline + 1;
	while (ft_strlen(map[frsline]) == 1)
	{
		frsline++;
		if (frsline == row)
			msg_err("The map needs to be in this universe.");
	}
	a->fconf.map.first_line = frsline;
}

void	manage_map(t_cub3d *a)
{
	is_space2map(a);
	review_map(a);
	map_algorithm(a);
}
