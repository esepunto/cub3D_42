/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/16 21:38:24 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Check if ther're chars forbidden on maze.
** The maze only accepts '0','1','2','N','S','E','W' and ' ' (space).
*/

static void	forbidd_chr(char c)
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
**  If c == E, dur = 0.
*/

static int	nbr_plyrs(int i, int j, t_cub3d *a)
{
	char	c;

	c = a->fconf.map.maze[i][j];
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
	{
		a->rayc.xplyr = j + 0.5;
		a->rayc.yplyr = i + 0.5;
		if (c == 'N')
			a->rayc.dirplyr -= M_PI_2;
		if (c == 'S')
			a->rayc.dirplyr += M_PI_2;
		if (c == 'W')
			a->rayc.dirplyr += M_PI;
		return (1);
	}
	else
		return (0);
}

/*
**  Check forbidden/repeat chars.
**  Check number of players.
*/

static void	review_maze(t_cub3d *a)
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

static void	frstlinemaze(t_cub3d *a)
{
	int		frsline;

	frsline = a->fconf.final_line_params + 1;
	while (a->fconf.map.maze[frsline][0] == '\0')
		frsline++;
	a->fconf.map.first_line = frsline;
}

void		manage_map(t_cub3d *a)
{
	frstlinemaze(a);
	review_maze(a);
	maze_algorithm(a);
}
