/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:13:10 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/12 13:00:48 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**
**
**    THE PROGRAM NOT USE THIS FT FOR THE MOMENT, IT SEEMS NOT NECESSARY
**
**
*/


/*
**  The algorith to found invalid maps its based.
**
**  There is an absolute truth to know if a map is closed: in each and every
**  line of the **  map (both horizontal and vertical): before an empty space
**  there will be a wall (1), and the next site (not space) there will be a
**  wall (1).
**
**  There are 2 exceptions: when a line begins and/or finishes with a wall (1),
**  because there cannot be a space before (when begins) nor space after (when
**  finishes).
**
**  So the following rules must be observed by the algorithm:
**		1.- The first character (not space on a map) must be a 1 (wall).
**		2.- The character before the next space (empty) after
**			that 1, must be a 1 (wall).
**		3.- The character after that space, that is not a space, has to
**			be a 1 (wall).
**		4.- And so on.
**		5.- It must be taken into account that the last character of the
**			line that is not a space, must necessarily be a 1 (wall).
**
**  The program uses 2 algorithms (horizontal / vertical lines).
*/

void	invalid_map_hor(int i, t_cub3d *a)
{
	int	len;
	int	j;

	len = ft_strlen(a->fconf.map.map[i]);
	j = 0;
	while (j < len)
	{
		while (ft_isspace(a->fconf.map.map[i][j]))
			j++;
		if (a->fconf.map.map[i][j] != '1' && a->fconf.map.map[i][j] != '\0')
			msg_err("58-Ops, this map is open. Review it or try with other map.");
		while (ft_isspace(a->fconf.map.map[i][j]) == 0 && j < len)
			j++;
		if (a->fconf.map.map[i][j] == '1')
			msg_err("62-Ops, this map is open. Review it or try with other map.");
	}
}
