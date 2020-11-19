/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look4params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:55:37 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/19 14:32:01 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** To find the path of texture's file
*/

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
**  This function returns a line (char *) with the params.
**  If find an error, stop the program and send message, but
**  don't manage all the errors because there's others functions
**  to do it.
*/


char	*look4_id(char *id, t_cub3d *a)
{
	int		i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < a->fconf.map.row)
	{
		j = 0;
		j = jump_sp(i, a);//"Quita" los espacios vacíos que haya al comienzo
		k = 0;
		while (k < ft_strlen(id) && a->fconf.map.map[i][j] == id[k])
		{
			if (ft_strlen(id) == k + 1)//Si hemos commprobado todos los caracteres del id
			{
				if (i > a->fconf.final_line_params)
					a->fconf.final_line_params = i;// Posiciona la última línea de los parámetros
				return(extract_path(id, a, i));// Para buscar el path/sendero del fichero (textura)
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
**  the id send by params ("NO", "WE", etc.), and save the line without spaces at
**  the beginning (deleted its when there's space at the beginning)
*/

char	*extract_path(const char *id, t_cub3d *a, int thisline)
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
			is_repeat(thisline, a, id);
			return (ft_strnstr(s1, id, len));
		}
		i++;
	}
	msg_err("Review the config file: something goes wrong.");
	return (0);
}

void	isthisaparam(t_cub3d *a)
{
	int		i;
	int		c;
	char	*map;
	char	*aux;
	char	*id[] = {"NO ", "SO ", "WE ", "EA ", "R ", "C ", "F ", "S "};

	i = 0;
	c = 0;
	while (i <= a->fconf.final_line_params)
	{
		aux = ft_strtrim(a->fconf.map.map[i], " ");
		map = ft_strtrim(aux, "	");
		free(aux);
		while (c <= 7 && map[0] != '\0'
			&& ft_strnstr(map, id[c], ft_strlen(id[c])) == NULL)
		{
			if (c == 7)
			{
				free(map);
				msg_err("There is line and isn't a param.");
			}
			c++;
		}
		free(map);
		i++;
		c = 0;
	}
}

void	find_params(t_cub3d *a)
{
	int		c;
	char	*id[] = {"NO ", "SO ", "WE ", "EA ", "R ", "C ", "F ", "S "};

	c = 0;
	while (c <= 7)
	{
		a->fconf.wall[c] = look4_id(id[c], a);
		a->fconf.wall_texture[c] = look4_texture(a->fconf.wall[c], id[c]);
		c++;
	}
	isthisaparam(a);
}
