/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:17:39 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 17:19:01 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** Check if anything param is repeat ("NO", "SO", etc.)
*/

void	is_repeat(int thisline, t_cub3d *a, const char *id)
{
	int			z;
	int			len;

	len = ft_strlen(id);
	thisline = thisline + 1;
	while (thisline < a->fconf.map.row)
	{
		z = 0;
		while (z < len && a->fconf.map.map[thisline][z] == id[z])
		{
			if (z == len - 1)
			{
				if (a->fconf.final_line_params < thisline)
					a->fconf.final_line_params = thisline;
				msg_err("No no no no: a param is repeat.");
			}
			z++;
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
