/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_fconfig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:57:29 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/06 14:27:56 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	save_fconfig(char *conf_file, t_cub3d *a)
{
	int			fd;
	char		*line;
	int			i;
	static int	c;

	c = 0;
	if ((fd = open(conf_file, O_RDONLY)) == -1)
		msg_err("This file is out of the air.");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		a->fconf.map.map[c] = ft_strdup(line);
		c++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
}

void	read_fconfig(char *conf_file, t_cub3d *a)
{
	calc_fconfig(conf_file, a);
	if (!(a->fconf.map.map = (char **)malloc(a->fconf.map.row * sizeof(char *))))
		msg_err("WTF! Give me back my memory!");
	save_fconfig(conf_file, a);
	find_walls(a);
}
