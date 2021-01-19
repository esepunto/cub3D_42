/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_manage_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 19:12:57 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*
**  Check invalid params
*/

static void	isthisaparam(t_cub3d *a)
{
	int		i;
	int		c;
	char	*map;
	char	**id;

	id = ft_split("NO ,SO ,WE ,EA ,S ,R ,C ,F ", ',');
	i = 0;
	while (i <= a->fconf.final_line_params)
	{
		c = 0;
		map = ft_delinitendblanks(a->fconf.map.maze[i]);
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
** Check if any param is repeat ("NO", "SO", etc.)
*/

static void	is_repeat(int thisline, t_cub3d *a, const char *id)
{
	int			z;
	int			len;

	len = ft_strlen(id);
	thisline += 1;
	while (thisline < a->fconf.map.row)
	{
		z = 0;
		while (z < len && a->fconf.map.maze[thisline][z] == id[z])
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
** Delete spaces and tabs from the begin and the end of texture.
** Replace tabs by spaces.
*/

static void	cleantexture(int c, t_cub3d *a)
{
	char	*str;

	str = ft_delinitendblanks(a->fconf.wall_texture[c]);
	str = ft_replacetabs(str);
	a->fconf.wall_texture[c] = str;
}

/*
** Return one line with one param iterative.
** Stops the program and returns a message when finds an error
*/

static char	*look4texture(char *id, size_t idlen, t_cub3d *a)
{
	int		i;
	char	*map;

	i = 0;
	while (i < a->fconf.map.row)
	{
		map = ft_delinitendblanks(a->fconf.map.maze[i]);
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
** Look for the parameters of config file to identify it.
**  _______________________________
**  |  char *id | c |   element   |
**  |___________|___|_____________|
**  |	"NO"    | 0 |    north    |
**  |	"SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**  |	"EA"    | 3 |    east     |
**  |	"S"     | 4 |   sprites   |
**  |	"R"     | 5 |  resolution |
**  |	"C"     | 6 |  ceilling   |
**  |	"F"     | 7 |    floor    |
**  |___________|___|_____________|
*/

void		manage_params(t_cub3d *a)
{
	int		c;
	char	**id;

	id = ft_split("NO ,SO ,WE ,EA ,S ,R ,C ,F ", ',');
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
