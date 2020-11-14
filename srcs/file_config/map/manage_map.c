/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/14 20:12:43 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  Next function review if 0,2,N,S,E or W are surrounded
**  by some space: in this case, the map is open.
*/

void	invalid_chrs_closed(int i, size_t j, t_cub3d *a)
{
	char	**map;

	map = a->fconf.map.map;
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j <= ft_strlen(map[i]))
		{
			if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if ((map[i - 1][j - 1] == ' ' && map[i - 1][j - 1])
					|| (map[i - 1][j + 1] == ' ' && map[i - 1][j + 1])
					|| (map[i + 1][j - 1] == ' ' && map[i + 1][j - 1])
					|| (map[i + 1][j + 1] == ' ' && map[i + 1][j + 1])
					|| (map[i][j + 1] == ' ' && map[i][j + 1])
					|| (map[i + 1][j] == ' ' && map[i + 1][j])
					|| (map[i][j - 1] == ' ' && map[i][j - 1])
					|| (map[i - 1][j] == ' ' && map[i - 1][j]))
					msg_err("The map's open. Don't go over the rainbow?");
			}
			j++;
		}
		i++;
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
** Check if yher're chars forbidden on map.
** The map only accepts '0','1','2','N','S','E','W' and ' ' (space).
*/

void	forbidd_chr(char c)
{
	if (c != '0' && c != '1' && c != '2' && c != ' ' && c != 'N'
			&& c != 'S'&& c != 'E'	&& c != 'W' && c != '\0')
	{
		msg_err("Forbidden characters in map");
	}
}

/*
**  To check enough space to map: blank line after params, etc.
*/

void	is_space2map(t_cub3d *a)
{
	char	**str;
	int		frsline;
	int		endline;
	int		row;

	str = a->fconf.map.map;
	row = a->fconf.map.row;
	endline = a->fconf.final_line_params;
	frsline = a->fconf.map.first_line;

	if (ft_strlen(str[endline + 1]) > 1)
		msg_err("I need a blank line before params");

	frsline= endline + 2;
	while (ft_strlen(str[frsline]) == 1)
	{
		frsline++;
		if (frsline == row)
			msg_err("The map needs to be in this universe.");
	}
	a->fconf.map.first_line = frsline;
}

/*
**  Next function check first line of the maps.
*/

void	check_frst_line_map(int i, size_t j, t_cub3d *a)
{
	if (i == a->fconf.map.first_line || i == a->fconf.map.row)
		if (a->fconf.map.map[i][j] != '1'
				&& a->fconf.map.map[i][j] != ' '
				&& a->fconf.map.map[i][j] != '\0')
		{
			msg_err("Invalid chars at the top/end.");
		}
}

void	check_end_line_map2(t_cub3d *a)
{
	int		i;
	size_t	j;

	j = 0;
	i = a->fconf.map.row - 1;
	while (j < ft_strlen(a->fconf.map.map[i]))
	{
		if (a->fconf.map.map[i][j] != '1'
				&& a->fconf.map.map[i][j] != ' '
				&& a->fconf.map.map[i][j] != '\0')
		{
			msg_err("Invalid chars at the end line.");
		}
		j++;
	}
}


void	check_frst_line_map2(t_cub3d *a)
{
	int		i;
	size_t	j;

	j = 0;
	i = a->fconf.map.first_line;
	while (j < ft_strlen(a->fconf.map.map[i]))
	{
		if (a->fconf.map.map[i][j] != '1'
				&& a->fconf.map.map[i][j] != ' '
				&& a->fconf.map.map[i][j] != '\0')
		{
			msg_err("Invalid chars at the top.");
		}
		j++;
	}
}

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
		if (c != '1')
			msg_err("Have tou see first columns of map?");
		i++;
	}
}

/*
**  Next function check some errors with above functions help:
**  and init the horizontal algorithm to check invalid maps.
*/

void	review_map_horiz(size_t j, t_cub3d *a)
{
	int		i;

	is_space2map(a);
//	check_frst_line_map(a);
	check_frst_line_map2(a);
	check_end_line_map2(a);
	check_frst_column(a);
	i = a->fconf.map.first_line;
	while (i < a->fconf.map.row)// ojo con el <=
	{
		j = 0;
		while (j < ft_strlen(a->fconf.map.map[i]))// ojo con el <=
		{
			if (ft_isprint(a->fconf.map.map[i][j]) == 1)
			{
				forbidd_chr(a->fconf.map.map[i][j]);
				repeat_chr(i, j, a);
			}
			j++;
		}
//		invalid_map_hor(i, a);// I THINK ITS NO NECESSARY, BUT DON'T DELETED
		i++;
	}
	if (a->fconf.map.num_players == 0)
		msg_err("Hey, the map can't run without player!");
}

void	find_map(t_cub3d *a)
{
	review_map_horiz(0, a);
	invalid_chrs_closed((a->fconf.final_line_params + 1), 0, a);
}
