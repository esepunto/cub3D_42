/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/09 23:23:34 by ssacrist         ###   ########.fr       */
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
	size_t	len;
	size_t	j;

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
		while (ft_isblank(map[j]) == 0)
			j++;
		if (map[j] == '1')
			msg_err("Ops, this map is open. Review it or try with other map.");
	}
}
/*
void	invalid_map_ver(const char **map)
{
	size_t	i;

}
*/

void	invalid_map_zeros(int i, size_t j, t_cub3d *a)
{
	char	**map;
	int		imax;
	size_t	jmax;

	imax = a->fconf.map.row;
	jmax = a->fconf.map.col;
	printf("imax: %d\n", imax);
	printf("jmax: %zu\n", jmax);
	map = a->fconf.map.map;
//	i =  i + 1;
	while (i < imax)
	{
		j = 0;
//		j = j + 1;
//		printf("map[%d][%zu]: |%c|\n", i, j, map[i][j]);
		while (j < ft_strlen(map[i]))
		{
//			printf("map[%d][%zu]: |%c|\n", i, j, map[i][j]);
			if (map[i][j] == '0')
			{
/*				printf("map[%d][%zu]: |%c|\n", i, j, map[i][j]);
				printf("i-1: %d\n", i-1);
				printf("i+1: %d\n", i+1);
				printf("j-1: %lu\n", j-1);
				printf("j+1: %lu\n", j+1);
*/				printf("map[i-1][j-1]: %c\n", map[i-1][j-1]);
				printf("map[i-1][j+1]: %c\n", map[i-1][j+1]);
				printf("map[i+1][j-1]: %c\n", map[+1][j-1]);
				printf("map[i+1][j+1]: %c\n", map[i+1][j+1]);
				printf("j+1: %lu\n", j+1);
				if (map[i-1][j-1] == 0)
					exit (0);
//					msg_err("The zeros of map are nor closed correctly.");
				else if (map[i+1][j-1] == '0')
					msg_err("The zeros of map are nor closed correctly.");
				else if (map[i-1][j+1] == '0')
					msg_err("The zeros of map are nor closed correctly.");
				else if (map[i+1][j+1] == '0')
					msg_err("The zeros of map are nor closed correctly.");
/*				{
					printf("map[i-1][j-1]: %c\n", map[i-1][j-1]);
					printf("map[i-1][j+1]: %c\n", map[i-1][j+1]);
					printf("map[i+1][j-1]: %c\n", map[+1][j-1]);
					printf("map[i+1][j+1]: %c\n", map[i+1][j+1]);
					printf("%c\n%c\n%c\n%c\n", map[i-1][j-1], map[i+1][j-1], map[i-1][j+1], map[i+1][j+1]);
					msg_err("The zeros of map are nor closed correctly.");
				}
*/			}
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

static void	repeat_chr(char c)
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

	chr_allowed = "012NSEW 	";
	i = 0;
	while (chr_allowed[i] != '\0')
	{
		if (c == chr_allowed[i])
			return ;
		else
			i++;
	}
	msg_err("Forbidden characters in map");
}

/*
**  Check some errors: chars forbidden, more than ine player and
**  init the horizontal algorithm to check invalid maps
*/

void 	review_map_horiz(t_cub3d *a, int i, int j)
{
	char	*map;
	int		imax;
	int		jmax;

	imax = a->fconf.map.row -1;
	jmax = a->fconf.map.col -1;
	map = a->fconf.map.map[i];
	while (i <= imax)
	{
		map = a->fconf.map.map[i];
		j = 0;
		while (j <= jmax && map[j] != '\0')
		{
			if (ft_isprint(map[j]) == 1)
			{
				forbidd_chr(map[j]);
				repeat_chr(map[j]);
			}
			j++;
		}
		invalid_map_hor(map);
		i++;
	}
}

void	find_map(t_cub3d *a)
{
//	review_map_horiz(a, 0, 0);
	invalid_map_zeros(0, 0, a);
}
