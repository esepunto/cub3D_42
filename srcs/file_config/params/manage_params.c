/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 23:51:23 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
**  To check invalid line at params
*/

void	isthisaparam(t_cub3d *a)
{
	int		i;
	int		c;
	char	*map;
	char	**id;

	id = ft_split("NO ,SO ,WE ,EA ,R ,C ,F ,S ", ',');
	i = 0;
	while (i <= a->fconf.final_line_params)
	{
		c = 0;
		map = ft_delinitendblanks(a->fconf.map.map[i]);
		while (c <= 7 && map[0] != '\0'
			&& ft_strnstr(map, id[c], ft_strlen(id[c])) == NULL)
		{
			if (c == 7)
				msg_err("There is line and isn't a param.");
			c++;
		}
		i++;
	}
	ft_delmatrix(id);
}

/*
**  This function returns a line (char *) with the params.
**  When finds an error, stops the program and returns a message.
*/

char	*look4texture(char *id, size_t idlen, t_cub3d *a)
{
	int		i;
	char	*map;

	i = 0;
	while (i < a->fconf.map.row)
	{
		map = ft_delinitendblanks(a->fconf.map.map[i]);
		if (ft_strnstr(map, id, idlen) != NULL)
		{
			if (i > a->fconf.final_line_params)
				a->fconf.final_line_params = i;
			is_repeat(i, a, id);
			return ((map + ft_strlen(id)));
		}
		i++;
	}
	msg_err("Review the config file: something goes wrong.");
	return (0);
}

/*
** This function looks for the params of config file to identify it.
**  _______________________________
**  |  char *id | c |   element   |
**  |___________|___|_____________|
**  |	"NO"    | 0 |    north    |
**  |	"SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**  |	"EA"    | 3 |    east     |
**  |	"R"     | 4 |  resolution |
**  |	"C"     | 5 |  ceilling   |
**  |	"F"     | 6 |    floor    |
**  |	"S"     | 7 |   sprites   |
**  |___________|___|_____________|
*/

void	manage_params(t_cub3d *a)
{
	int		c;
	char	**id;

	id = ft_split("NO ,SO ,WE ,EA ,R ,C ,F ,S ", ',');
	c = 0;
	while (c <= 7)
	{
		a->fconf.wall_texture[c] = look4texture(id[c], ft_strlen(id[c]), a);
		cleantexture(c, a);
		c++;
	}
	ft_delmatrix(id);
	isthisaparam(a);
	review_params(a);
}
