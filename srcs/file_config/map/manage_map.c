/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/10 14:35:18 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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


void	invalid_map_hor(const char *map)
{
	int	len;
	int	j;

	len = ft_strlen(map);
	j = 0;
	if (map[0] == '\0')
		return ;
	if ((map[0] != '1' && ft_isblank(map[0]) == 0)
				|| (map[len - 1] != '1' && ft_isblank(map[len - 1]) == 0))
		msg_err("Ops, this map is open. Review it or try with other map.");
	while (j < len)
	{
		while (ft_isblank(map[j]))
			j++;
		if (map[j] != '1' && map[j] != '\0')
			msg_err("Ops, this map is open. Review it or try with other map.");
		while (ft_isspace(map[j]) == 0 && j < len)
			j++;
		if (map[j] == '1')
			msg_err("Ops, this map is open. Review it or try with other map.");
	}
}

void	zero_not_closed(int i, size_t j, t_cub3d *a)
{
	if (a->fconf.map.map[i-1][j-1] == ' '
		|| a->fconf.map.map[i-1][j+1] == ' '
		|| a->fconf.map.map[i+1][j-1] == ' '
		|| a->fconf.map.map[i+1][j+1] == ' ')
	{
		msg_err("The zeros of map are nor closed correctly.");
	}
}

/*
**  This function review if zeros are surrounded
**  by some space: in this case, the map is open.
*/

void	invalid_map_zeros(int i, size_t j, t_cub3d *a)
{
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j < ft_strlen(a->fconf.map.map[i]))
		{
			if (a->fconf.map.map[i][j] == '0')
				zero_not_closed(i, j, a);
			j++;
		}
		i++;
	}
}

/*
** Add chars N, S, W and E from map.
** If there's more than one, return error because
** not accept more than one player.
*/

void	repeat_chr(char c)
{
	static int count;

	if (!count)
		count = 0;
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			count++;
	if (count > 1)
		msg_err("Sorry, I can't accept two players.");
}

/*
** Check chars forbidden on map
*/

void	forbidd_chr(char c)
{
	char	*chr_allowed;
	int		i;

	chr_allowed = "012NSEW";
	i = 0;
	while (i <= 6)
	{
		if (c == chr_allowed[i] || chr_allowed[i] == ' ')
			return ;
		i++;
	}
	if (i == 6)
	{
			printf("chr forbidd: |%c|\n", c);
			msg_err("Forbidden characters in map");
	}
}

/*
**  Check some errors: chars forbidden, more than ine player and
**  init the horizontal algorithm to check invalid maps
*/

void 	review_map_horiz(int i, size_t j, t_cub3d *a)
{
	int		imax;
	size_t	jmax;

	imax = a->fconf.map.row;
	jmax = a->fconf.map.col;
	while (i < imax)
	{
		j = 0;
		while (j < jmax)
		{
			if (i == 0 && a->fconf.map.map[i][j] == '0')
				msg_err("Zeros at the top");
			if (ft_isprint(a->fconf.map.map[i][j]) == 1)
			{
				forbidd_chr(a->fconf.map.map[i][j]);
				repeat_chr(a->fconf.map.map[i][j]);
			}
			j++;
		}
		invalid_map_hor(a->fconf.map.map[i]);
		i++;
	}
}

void	find_map(t_cub3d *a)
{
	review_map_horiz(0, 0, a);
	invalid_map_zeros(0, 0, a);
}
