/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fconfig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 11:55:37 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

char	look4_id(char *id, t_cub3d *a, int len)
{
	int		i;
	int		j;
	int		k;
	
	i = 0;
	while (i < a->fconf.map.row)
	{
		j = 0;
		k = 0;
		j = del_sp(i, j, a);
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
}

void	find_walls(t_cub3d *a)
{
	a->fconf.wallno = (look4_id("NO ", a, 2));
	a->fconf.wallso = (look4_id("SO ", a, 3));
	a->fconf.wallwe = (look4_id("WE ", a, 3));
	a->fconf.wallea = (look4_id("EA ", a, 3));
	a->fconf.res = (look4_id("R ", a, 2));
	a->fconf.ceil = (look4_id("C ", a, 2));
	a->fconf.flr = (look4_id("F ", a, 2));
	a->fconf.sprite = (look4_id("S ", a, 2));
}