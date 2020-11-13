/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:35 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/13 11:58:23 by ssacrist         ###   ########.fr       */
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

	len = ft_strlen(a->fconf.wall_texture[c]);
	i = 0;
	while (i <= len)
	{
		while(ft_isblank(a->fconf.wall_texture[c][i]))
			i++;
		a->fconf.nb_wrd_param++;
		while(ft_isprint(a->fconf.wall_texture[c][i]))
			i++;
	}
	return (a->fconf.nb_wrd_param);
}

void	rev_walls(int c, t_cub3d *a)
{
	if (ft_count_wrds(c, a) > 1)
		msg_err("Too much information in params.");
}

void	review_params(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c <= 7)
	{
		if (c < 4 || c == 7)
			rev_walls(c, a);// One ft for all walls??
/*		if (c >= 5 && c <= 6)
			rev_cefl(c, a);
		if (c == 4)
			rev_res(a);*/
		c++;
	}
	return ;
/*		rev_no(0, a);// One ft for anyone wall??rev_so(1, a);rev_we(2, a);
		rev_ea(3, a);
		rev_r(4, a);
		rev_c(5, a);
		rev_c(6, a);
		rev_s(7, a);*/
}
