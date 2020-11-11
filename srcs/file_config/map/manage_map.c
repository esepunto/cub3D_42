/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 10:32:12 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/11 14:43:33 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	zero_not_closed(int i, size_t j, t_cub3d *a)
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
			if (a->fconf.map.map[i][j] == '0'
				|| a->fconf.map.map[i][j] == '2'
				|| a->fconf.map.map[i][j] == 'N'
				|| a->fconf.map.map[i][j] == 'S'
				|| a->fconf.map.map[i][j] == 'E'
				|| a->fconf.map.map[i][j] == 'W')
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

void	repeat_chr(int i, size_t j, t_cub3d *a)
{
	static int count;

	if (!count)
		count = 0;
	if (a->fconf.map.map[i][j] == 'N' || a->fconf.map.map[i][j] == 'S'
		|| a->fconf.map.map[i][j] == 'W' || a->fconf.map.map[i][j] == 'E')
	{
		count++;
	}
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
**  Check some errors: chars forbidden, more than one player and
**  init the horizontal algorithm to check invalid maps
*/

void	review_map_horiz(size_t j, t_cub3d *a)
{
	int		frst_horiz;
	int		i;

	frst_horiz = a->fconf.final_line_params + 1;
	while (ft_strlen(a->fconf.map.map[frst_horiz]) == 1)
		frst_horiz++;
	i = frst_horiz;
	while (i < a->fconf.map.row)
	{
		j = 0;
		while (j < a->fconf.map.col)
		{
			if (i == frst_horiz && a->fconf.map.map[i][j] == '0')
				msg_err("Zeros at the top");
			if (ft_isprint(a->fconf.map.map[i][j]) == 1)
			{
				forbidd_chr(a->fconf.map.map[i][j]);
				repeat_chr(i, j, a);
			}
			j++;
		}
		invalid_map_hor(i, a);
		i++;
	}
}

void	find_map(t_cub3d *a)
{
	review_map_horiz(0, a);
	invalid_map_zeros((a->fconf.final_line_params + 1), 0, a);
}
