/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:13:10 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/20 11:44:51 by ssacrist         ###   ########.fr       */
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
**  Next two functions review if 0,2,N,S,E or W are surrounded
**  by some space: in this case, the map is open and return error message.
*/

void	surrounded(int i, size_t j, char **map)
{
	if ((map[i - 1][j - 1] == ' ')// || map[i - 1][j - 1] == '\0')
		|| (map[i - 1][j + 1] == ' ')// || map[i - 1][j + 1] == '\0')
		|| (map[i + 1][j - 1] == ' ')// || map[i + 1][j - 1] == '\0')
		|| (map[i + 1][j + 1] == ' ')// || map[i + 1][j + 1] == '\0')
		|| (map[i][j + 1] == ' ')// || map[i][j + 1] == '\0')
		|| (map[i + 1][j] == ' ')// || map[i + 1][j] == '\0')
		|| (map[i][j - 1] == ' ')// || map[i][j - 1] == '\0')
		|| (map[i - 1][j] == ' '))// || map[i - 1][j] == '\0'))
	{
		msg_err("The map's open. Don't go over the rainbow?");
	}
}

void	map_algorithm(t_cub3d *a)
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
				surrounded(i, j, map);
			j++;
		}
		i++;
	}
}
