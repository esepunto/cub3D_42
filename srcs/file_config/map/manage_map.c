/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 23:30:07 by ssacrist         ###   ########.fr       */
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
**  Check if there're more than one player.
*/

int		nbr_players(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

/*
**  Check forbidden/repeat chars
**  and minimum number of players.
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
				a->fconf.map.num_players += nbr_players(a->fconf.map.map[i][j]);
			}
			j++;
		}
		i++;
	}
	if (a->fconf.map.num_players != 1)
		msg_err("Hey! Only player, and one only, is accepted.");
}

/*
**  Save the first line of map
*/

void	is_space2map(t_cub3d *a)
{
	int		frsline;

	frsline = a->fconf.final_line_params + 1;
	while (ft_strlen(a->fconf.map.map[frsline]) == 1)
		frsline++;
	a->fconf.map.first_line = frsline;
}

void	manage_map(t_cub3d *a)
{
	is_space2map(a);
	review_map(a);
	map_algorithm(a);
}
