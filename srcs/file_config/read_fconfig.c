/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fconfig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/07 14:25:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*look4_texture(char	*str, char	*id)
{
	size_t	i;

	i = ft_strlen(id);
	while (ft_isblank(str[i]))
		i++;
	str = ft_substr(str, i, ft_strlen(str) - i);
	return (str);
}

/*
**  This function dismiss blank spaces at the beginning of
**  any line of the config file (except in map's lines, of course)
*/

int		del_sp(int i, int j, t_cub3d *a)
{
	int	aux;

	aux = a->fconf.map.map[i][j];
	while (ft_isblank(aux))
	{
		j++;
		aux = a->fconf.map.map[i][j];
	}
	return (j);
}

void	is_repeat(int m, t_cub3d *a, const char *id)
{
	char	**s1;
	int			i;
	int			j;
	int			z;
	int			len;

	len = ft_strlen(id);
	i = m + 1;
	s1 = a->fconf.map.map;
	while (i < a->fconf.map.row)
	{
		j = del_sp(i, 0, a);
		z = 0;
		while (z < len && s1[i][j] == id[z])
		{
			if (z == len - 1)
				msg_err("No no no no: a param is repeat.");
			z++;
			j++;
		}
		i++;
	}
	return ;
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
	size_t	k;

	i = 0;
	while (i < a->fconf.map.row)
	{
		j = 0;
		j = del_sp(i, j, a);
		a->fconf.init_id[c] = j;
		k = 0;
		while (k < ft_strlen(id))
		{
			if (a->fconf.map.map[i][j] != id[k])
				break ;
			if (ft_strlen(id) == k + 1)
			{
//				return (a->fconf.map.map[i]);
				return(look4_id_2(id, a, i));
			}
			j++;
			k++;
		}
		i++;
	}
	msg_err("Review the config file: something goes wrong.");
	return (0);
}

/*
**  This function returns, like *look4_id, the line when
**  the id send by params ("NO", "WE", etc.), but its behaviour is
**  a little diferent because its save the line without spaces at
**  the beginning (deleted its when there's space at the beginning)
**
**  Also, I think this function (look4_id_2) is more readable
**  than *look4_id, instead both functions manage the same errors.
*/

char	*look4_id_2(const char *id, t_cub3d *a, int m)
{
	size_t		len;
	const char	*s1;
	int			i;

	i = 0;
	while (i < a->fconf.map.row)
	{
		s1 = a->fconf.map.map[i];
		len = ft_strlen(s1);
		if (ft_strnstr(s1, id, len))
		{
			is_repeat(m, a, id);
			return (ft_strnstr(s1, id, len));
		}
		i++;
	}
	msg_err("Review the config file: something goes wrong.");
	return (0);
}

void	find_walls(t_cub3d *a)
{
	int		c;
	char	*id[] = {"NO ", "SO ", "WE ", "EA ", "R ", "C ", "F ", "S "};

	c = 0;
	while (c <= 7)
	{
		a->fconf.wall[c] = look4_id(id[c], a, ft_strlen(id[c]));
		a->fconf.wall_texture[c] = look4_texture(a->fconf.wall[c], id[c]);
		c++;
	}
}


/*
void	find_walls_2(t_cub3d *a)
{
	a->fconf.wallno = look4_id("NO ", a, 3);
	a->fconf.wallno_texture = look4_texture(a->fconf.wallno, "NO ");
	a->fconf.wallso = look4_id("SO ", a, 3);
	a->fconf.wallso_texture = look4_texture(a->fconf.wallso, "SO ");
	a->fconf.wallwe = look4_id("WE ", a, 3);
	a->fconf.wallwe_texture = look4_texture(a->fconf.wallwe, "WE ");
	a->fconf.wallea = look4_id("EA ", a, 3);
	a->fconf.wallea_texture = look4_texture(a->fconf.wallea, "EA ");
	a->fconf.res = look4_id("R ", a, 2);
//	a->fconf.res = look4_id("R ", a, 4);
	a->fconf.ceil = look4_id("C ", a, 2);
//	a->fconf.ceil = look4_id("C ", a, 5);
	a->fconf.flr = look4_id("F ", a, 2);
//	a->fconf.flr = look4_id("F ", a, 6);
	a->fconf.sprite = look4_id("S ", a, 2);
	a->fconf.sprite_texture = look4_texture(a->fconf.sprite, "S ");
}
*/
