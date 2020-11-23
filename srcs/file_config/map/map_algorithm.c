/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:13:10 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 18:08:09 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  Next two functions review if 0,2,N,S,E or W are surrounded
**  by some space: in this case, the map is open and return error message.
*/

void	surrounded(int i, size_t j, char **map, t_cub3d *a)
{
	if (i - 1 == a->fconf.final_line_params
		|| (map[i - 1][j - 1] == ' ' || map[i - 1][j - 1] == '\0')
		|| (map[i - 1][j + 1] == ' ' || map[i - 1][j + 1] == '\0')
		|| (map[i + 1][j - 1] == ' ' || map[i + 1][j - 1] == '\0')
		|| (map[i + 1][j + 1] == ' ' || map[i + 1][j + 1] == '\0')
		|| (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
		|| (map[i + 1][j] == ' ' || map[i + 1][j] == '\0')
		|| (map[i][j - 1] == ' ' || map[i][j - 1] == '\0')
		|| (map[i - 1][j] == ' ' || map[i - 1][j] == '\0'))
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
				surrounded(i, j, map, a);
			j++;
		}
		i++;
	}
}
