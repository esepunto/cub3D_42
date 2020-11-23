/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:17:39 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 12:35:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  This function dismiss blank spaces at the beginning of
**  any line of the config file (except in map's lines, of course)
*/

int		jump_sp(int i, t_cub3d *a)
{
	char	aux;
	size_t	j;

	j = 0;
	aux = a->fconf.map.map[i][j];
	while (ft_isblank(aux))
	{
		j++;
		aux = a->fconf.map.map[i][j];
	}
	return (j);
}

/*
** Check if anything param is repeat ("NO", "SO", etc.)
*/

void	is_repeat(int thisline, t_cub3d *a, const char *id)
{
	int			j;
	int			z;
	int			len;

	len = ft_strlen(id);
	thisline = thisline + 1;
	while (thisline < a->fconf.map.row)
	{
		j = jump_sp(thisline, a);
		z = 0;
		while (z < len && a->fconf.map.map[thisline][j] == id[z])
		{
			if (z == len - 1)
			{
				if (a->fconf.final_line_params < thisline)
					a->fconf.final_line_params = thisline;
				msg_err("No no no no: a param is repeat.");
			}
			z++;
			j++;
		}
		thisline++;
	}
	return ;
}

/*
** To replace tabs by spaces
*/

char	*replacetabs(char *str)
{
	size_t	c;

	c = 0;
	while (c <= ft_strlen(str))
	{
		if (str[c] == '	')
			str[c] = ' ';
		c++;
	}
	return (str);
}

/*
** To deleted spaces and tabs and
** replace tabs by spaces from the
** begin and the end of texture
*/

void	cleantexture(int c, t_cub3d *a)
{
	char	*str;

	str = ft_delinitendblanks(a->fconf.wall_texture[c]);
	str = replacetabs(str);
	a->fconf.wall_texture[c] = str;
}
