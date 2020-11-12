/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/12 13:20:23 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  Next function review if 0,2,N,S,E or W are surrounded
**  by some space: in this case, the map is open.
*/

void	invalid_chrs_closed(int i, size_t j, t_cub3d *a)
{
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j < ft_strlen(a->fconf.map.map[i]))
		{
			if (a->fconf.map.map[i][j] == '0' || a->fconf.map.map[i][j] == '2'
			|| a->fconf.map.map[i][j] == 'N' || a->fconf.map.map[i][j] == 'S'
			|| a->fconf.map.map[i][j] == 'E' || a->fconf.map.map[i][j] == 'W')
			{
				if (a->fconf.map.map[i - 1][j - 1] == ' '
					|| a->fconf.map.map[i - 1][j + 1] == ' '
					|| a->fconf.map.map[i + 1][j - 1] == ' '
					|| a->fconf.map.map[i + 1][j + 1] == ' '
					|| a->fconf.map.map[i][j + 1] == ' '
					|| a->fconf.map.map[i + 1][j] == ' '
					|| a->fconf.map.map[i][j - 1] == ' '
					|| a->fconf.map.map[i - 1][j + 1] == ' ')
				{
					msg_err("The map's open. Don't go over the rainbow?");
				}
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
		msg_err("Sorry, I can't accept two players.");
}

/*
** Check if yher're chars forbidden on map.
** The map only accepts '0','1','2','N','S','E','W' and ' ' (space).
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
		msg_err("Forbidden characters in map");
}

/*
**  To check enough space to map: blank line after params, etc.
*/

void	is_space2map(t_cub3d *a)
{
	if (a->fconf.map.row - a->fconf.final_line_params < 3)// revisar si 3 o 4
		msg_err("The map needs to be in this universe.");
	if (ft_strlen(a->fconf.map.map[a->fconf.final_line_params + 1]) > 1)//revisar que acepta espacios vacíos
		msg_err("I need a blank line before params");
	a->fconf.map.first_line = a->fconf.final_line_params + 2;
	while (ft_strlen(a->fconf.map.map[a->fconf.map.first_line]) == 1)
	{
		a->fconf.map.first_line++;
		if (a->fconf.map.first_line == a->fconf.map.row)
			msg_err("The map needs to be in this universe.");
	}
}

/*
**  Next function check first line of the maps.
*/

void	check_frst_line_map(int i, size_t j, t_cub3d *a)
{
	if (i == a->fconf.map.first_line)
		if (a->fconf.map.map[i][j] != '1'
				&& a->fconf.map.map[i][j] != ' '
				&& a->fconf.map.map[i][j] != '\0')
		{
			msg_err("Invalid chars at the top.");
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

/*
**  Next function check some errors with above functions help:
**  and init the horizontal algorithm to check invalid maps.
*/

void	review_map_horiz(size_t j, t_cub3d *a)
{
	int		i;

	is_space2map(a);
	check_frst_line_map2(a);
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
