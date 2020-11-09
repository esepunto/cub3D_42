/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/09 18:04:54 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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

void 	review_map_horiz(t_cub3d *a, int i, int j)
{
	char	*map;
	int		imax;
	int		jmax;

	imax = a->fconf.map.row -1;
	jmax = a->fconf.map.col -1;
	map = a->fconf.map.map[i];
//	printf("imax: |%d|\n", imax);
//	printf("jmax: |%d|\n", jmax);
//	printf(" map: |%s|\n", map);
//	printf("   i: |%d|\n", i);
//	printf("   j: |%d|\n", j);
	while (i <= imax)
	{
		map = a->fconf.map.map[i];
		j = 0;
		while (j <= jmax && map[j] != '\0')
		{
			if (ft_isprint(map[j]) == 1)
			{
//				printf("map[%d]  pre: |%c|\n", j, map[j]);
				forbidd_chr(map[j]);
//				printf("map[%d] post: |%c|\n", j, map[j]);
				repeat_chr(map[j]);
			}
			j++;
		}
		i++;
//		map = a->fconf.map.map[i];
	}
}

void	find_map(t_cub3d *a)
{
	review_map_horiz(a, 0, 0);
}
