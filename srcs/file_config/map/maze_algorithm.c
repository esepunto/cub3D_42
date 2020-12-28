/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:13:10 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/28 00:21:00 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  Next two functions review if 0,2,N,S,E or W are surrounded
**  by some space: in this case, the maze is open and return error message.
*/

static void	surrounded(int i, size_t j, char **maze, t_cub3d *a)
{
	if (i - 1 == a->fconf.final_line_params
		|| (maze[i - 1][j - 1] == ' ' || maze[i - 1][j - 1] == '\0')
		|| (maze[i - 1][j + 1] == ' ' || maze[i - 1][j + 1] == '\0')
		|| (maze[i + 1][j - 1] == ' ' || maze[i + 1][j - 1] == '\0')
		|| (maze[i + 1][j + 1] == ' ' || maze[i + 1][j + 1] == '\0')
		|| (maze[i][j + 1] == ' ' || maze[i][j + 1] == '\0')
		|| (maze[i + 1][j] == ' ' || maze[i + 1][j] == '\0')
		|| (maze[i][j - 1] == ' ' || maze[i][j - 1] == '\0')
		|| (maze[i - 1][j] == ' ' || maze[i - 1][j] == '\0'))
	{
		msg_err("The maze's open and you could be absorbed by a blackhole.");
	}
}

void		maze_algorithm(t_cub3d *a)
{
	char	**maze;
	int		i;
	size_t	j;

	maze = a->fconf.map.maze;
	i = a->fconf.map.first_line;
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j <= ft_strlen(maze[i]))
		{
			if (maze[i][j] == '0' || maze[i][j] == '2' || maze[i][j] == 'N'
				|| maze[i][j] == 'S' || maze[i][j] == 'E' || maze[i][j] == 'W')
			{
				if (maze[i][j] == '2')
					a->fconf.map.num_sprites++;
				surrounded(i, j, maze, a);
			}
			j++;
		}
		i++;
	}
}
