/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:13:10 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/16 11:12:42 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** Check if yher're chars forbidden on map.
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
** It counts the number os players.
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
**  This function checks forbideen chars
**  and the number os players.
*/

void	review_map_horiz(t_cub3d *a)
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
**  Next function review if 0,2,N,S,E or W are surrounded
**  by some space: in this case, the map is open.
*/

void	map_open_algorithm(t_cub3d *a)
{
	char	**map;
	int		i;
	size_t	j;

	map = a->fconf.map.map;
	i = a->fconf.map.first_line;
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j <= ft_strlen(map[i]))
		{
			if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (map[i - 1][j - 1] == ' ' || map[i - 1][j + 1] == ' '
					|| map[i + 1][j - 1] == ' ' || map[i + 1][j + 1] == ' '
					|| map[i][j + 1] == ' ' || map[i + 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i - 1][j] == ' ')
					msg_err("The map's open. Don't go over the rainbow?");
			}
			j++;
		}
		i++;
	}
}
