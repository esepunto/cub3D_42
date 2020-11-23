/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 10:51:14 by ssacrist         ###   ########.fr       */
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
		map = a->fconf.map.map[i];
		map = ft_delinitblanks(map);
		map = ft_delendblanks(map);
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
** To find the path of texture's file
*/

char	*look4_texture(char *str, char *id)
{
	size_t	i;

	i = ft_strlen(id);
	while (ft_isblank(str[i]))
		i++;
	str = ft_substr(str, i, ft_strlen(str) - i);
	return (str);
}

/*
**  This function returns a line (char *) with the params.
**  If find an error, stop the program and send message, but
**  don't manage all the errors because there's others functions
**  to do it.
*/

char	*look4_id(char *id, size_t idlen, t_cub3d *a)
{
	int		i;
	char	*map;

	i = 0;
	while (i < a->fconf.map.row)
	{
		map = a->fconf.map.map[i];
		map = ft_delinitendblanks(map);
		if (ft_strnstr(map, id, idlen) != NULL)
		{
			if (i > a->fconf.final_line_params)
				a->fconf.final_line_params = i;
			is_repeat(i, a, id);
			map = look4_texture(map, id);
			return (map);
		}
		i++;
	}
	msg_err("Review the config file: something goes wrong.");
	return (0);
}


/*
** This function look for the params of config file to identify it.
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
		a->fconf.wall_texture[c] = look4_id(id[c], ft_strlen(id[c]), a);
		c++;
	}
	ft_delmatrix(id);
	isthisaparam(a);
	review_params(a);
}
