/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:35 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/13 13:14:06 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** The info of any param is at a->fconf.wall_texture[c], where
** 'c' is a var that corresponds to:
**  _______________________________
**	|  param    | c |   element   |
**	|___________|___|_____________|
**	|   "NO"    | 0 |    north    |
**	|   "SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**	|	"EA"    | 3 |    east     |
**	|	"R"     | 4 |  resolution |
**	|	"C"     | 5 |  ceilling   |
**	|	"F"     | 6 |    floor    |
**	|	"S"     | 7 |   sprites   |
**  |___________|___|_____________|
*/

int	ft_count_wrds(int c, t_cub3d *a)
{
	int	len;
	int	i;
	int	count;

	count = 0;
	len = ft_strlen(a->fconf.wall_texture[c]);
	i = 0;
	while (i <= len)
	{
		while(ft_isblank(a->fconf.wall_texture[c][i]))
			i++;
		if(ft_isprint(a->fconf.wall_texture[c][i]) && !ft_isblank(a->fconf.wall_texture[c][i]))
			count++;
		i++;
		while (ft_isprint(a->fconf.wall_texture[c][i]) && !ft_isblank(a->fconf.wall_texture[c][i]))
			i++;
		i++;
	}
	return (count);
}

/*
** Next 3 functions check the number os params in:
** 		a) walls and sprites
** 		b) floor and ceilling
** 		c) resolution
*/

void	rev_walls(int c, t_cub3d *a)
{
	if (ft_count_wrds(c, a) != 1)
		msg_err(" information in walls.");
}

void	rev_cefl(int c, t_cub3d *a)
{
	if (ft_count_wrds(c, a) != 1)
		msg_err("Poor information in floor/ceilling.");
}

void	rev_res(int c, t_cub3d *a)
{
	if (ft_count_wrds(c, a) != 2)
		msg_err("Poor information in resolution.");
}

void	review_params(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c <= 7)
	{
		if (c < 4 || c == 7)
			rev_walls(c, a);
		if (c >= 5 && c <= 6)
			rev_cefl(c, a);
		if (c == 4)
			rev_res(c, a);
		c++;
	}
}
