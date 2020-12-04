/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/04 13:19:59 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** Check if ther're chars forbidden on maze.
** The maze only accepts '0','1','2','N','S','E','W' and ' ' (space).
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
**  Count number of players.
**  Save position and direction of player.
*/

int		nbr_plyrs(int i, int j, t_cub3d *a)
{
	char	c;

	c = a->fconf.map.maze[i][j];
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
	{
		a->steal.xplyr = j;
		a->steal.yplyr = i;
		if (c == 'N')
			a->steal.dirplyr -= 0;
		if (c == 'S')
			a->steal.dirplyr -= 1.5;
		if (c == 'W')
			a->steal.dirplyr += 3.0;
		if (c == 'E')
			a->steal.dirplyr += 1.5;
		return (1);
	}
	else
		return (0);
}

/*
**  Check forbidden/repeat chars.
**  Check number of players.
*/

void	review_maze(t_cub3d *a)
{
	int		i;
	size_t	j;

	i = a->fconf.map.first_line;
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j < ft_strlen(a->fconf.map.maze[i]))
		{
			if (ft_isprint(a->fconf.map.maze[i][j]) == 1)
			{
				forbidd_chr(a->fconf.map.maze[i][j]);
				a->fconf.map.num_players += nbr_plyrs(i, j, a);
			}
			j++;
		}
		i++;
	}
	if (a->fconf.map.num_players != 1)
		msg_err("Hey! Only a player, and one only, is accepted.");
}

/*
**  Look for the first line of maze
*/

void	frstlinemaze(t_cub3d *a)
{
	int		frsline;

	frsline = a->fconf.final_line_params + 1;
	while (a->fconf.map.maze[frsline][0] == '\0')
		frsline++;
	a->fconf.map.first_line = frsline;
	a->fconf.map.nbrlines = a->fconf.map.row - a->fconf.map.first_line;
}

void	manage_map(t_cub3d *a)
{
	frstlinemaze(a);
	review_maze(a);
	maze_algorithm(a);
}
