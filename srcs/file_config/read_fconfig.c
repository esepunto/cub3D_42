/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fconfig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 18:11:31 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
**  This function dismiss blank spaces at the beginning of
**  any line of the config file (except in map's lines, of course)
*/
int		del_sp(int i, int j, t_cub3d *a)
{
	int	aux;

	aux = a->fconf.map.map[i][j];
	while (aux == '\n' || aux == '\t' || aux == '\r' || aux == '\v'
			|| aux == '\f' || aux == '\b' || aux == '\r' || aux == '\\'
			|| aux == ' ' || aux == '\t')
	{	
		j++;
		aux = a->fconf.map.map[i][j];
	}
	return (j);
}

/*
** This function look for the params of config file to identify it.
**  _______________________________ 
**	|  char *id | c |   element   |
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
**
**  This function saves de initial position of the
**  params in struct a.dconf.init_id[c] (see table above fior 'c')
**
**  This function returns a line (char *) with the params. 
**  If find an error, stop the program and send message, but
**  don't manage all the errors because there's others functions
**  to do it.
**
**  Variable len is the lenggitSth of *id + 1: it helps to identify
**  an error (not space after id "NO", "EA", etc. in config file)  
*/

char	*look4_id(char *id, t_cub3d *a, int c)
{
	int		i;
	int		j;
	int		k;
	int 	len;
		
	i = 0;
	len = ft_strlen(id);
	while (i < a->fconf.map.row)
	{
		j = 0;
		k = 0;
		j = del_sp(i, j, a);
		a->fconf.init_id[c] = j;
		while (k < len)
		{
			if (a->fconf.map.map[i][j] != id[k])
				break ;
			if (len == k + 1)
				return (a->fconf.map.map[i]);
			j++;
			k++;
		}
		i++;
	}
	msg_err("Review the config file: something goes wrong.");
	return (0);
}

void	find_walls(t_cub3d *a)
{
	a->fconf.wallno = (look4_id("NO ", a, 0));
//	errors_mgmt("NO", a, 0);
	a->fconf.wallso = (look4_id("SO ", a, 1));
//	errors_mgmt("SO", a, 1);
	a->fconf.wallwe = (look4_id("WE ", a, 2));
//	errors_mgmt("WE", a, 2);
	a->fconf.wallea = (look4_id("EA ", a, 3));
//	errors_mgmt("EA", a, 3);
	a->fconf.res = (look4_id("R ", a, 4));
	a->fconf.ceil = (look4_id("C ", a, 5));
	a->fconf.flr = (look4_id("F ", a, 6));
	a->fconf.sprite = (look4_id("S ", a, 7));
}
