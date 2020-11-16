/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readnsave_fconfig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:57:29 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/16 11:13:40 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Save every line of the file config
** in a new line in struct a.fconf.map.map
*/

void	save_fconfig(char *conf_file, t_cub3d *a)
{
	int			fd;
	char		*line;
	int			i;
	static int	c;
	char		*aux;

	c = 0;
	if ((fd = open(conf_file, O_RDONLY)) == -1)
		msg_err("This file is out of the air.");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		a->fconf.map.map[c] = ft_strdup(line);
		aux = a->fconf.map.map[c];
		free(a->fconf.map.map[c]);
//		a->fconf.map.map[c] = ft_strjoin(ft_strdup(a->fconf.map.map[c]), " ");
		a->fconf.map.map[c] = ft_strjoin(ft_strdup(aux), " ");
		free(aux);
		c++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
}

/*
** Calculate colums and rows,
** and return error if config file isn't exist
*/

void	calc_fconfig(char *conf_file, t_cub3d *a)
{
	int		fd;
	char	*line;
	int		i;
	size_t	columnas;

	line = NULL;
	if ((fd = open(conf_file, O_RDONLY)) == -1)
		msg_err("Please, type carefully. This file is out of the air.");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		columnas = ft_strlen(line);
		if (columnas > a->fconf.map.col)
			a->fconf.map.col = columnas;
		free(line);
		line = NULL;
		a->fconf.map.row++;
	}
	free(line);
	line = NULL;
	close(fd);
}

/*
** This ft is the Big Bang: the beginning of everything, so
** the beginning of 42 :p
*/

void	open_fconfig(char *conf_file, t_cub3d *a)
{
	calc_fconfig(conf_file, a);
	if (!(a->fconf.map.map = (char **)malloc(a->fconf.map.row * sizeof(char *))))
		msg_err("WTF! Give me back my memory!");
	save_fconfig(conf_file, a);
//	print_fconfig(a);
	find_walls(a);
	review_params(a);
//	print_fconfig(a);
//	find_walls_2(a);
	find_map(a);
//	print_fconfig(a);
}
