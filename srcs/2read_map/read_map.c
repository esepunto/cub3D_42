/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 09:08:57 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calc_map(char *conf_file, t_cub3d *a)
{
	int		fd;
	char	*line;
	int		i;
	size_t	columnas;

	line = NULL;
	if ((fd = open(conf_file, O_RDONLY)) == -1)
		perror("Error\n");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		columnas = ft_strlen(line);
		if (columnas > a->map.col)
			a->map.col = columnas;
		free(line);
		line = NULL;
		a->map.row++;
	}
	free(line);
	line = NULL;
	close(fd);
}

void	save_map(char *conf_file, t_cub3d *a)
{
	int			fd;
	char		*line;
	int			i;
	static int	c;

	c = 0;
	if ((fd = open(conf_file, O_RDONLY)) == -1)
		perror("Error\n");
	while ((i = get_next_line(fd, &line)) > 0)
	{
		a->map.map[c] = ft_strdup(line);
		c++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
}

void	read_map(char *conf_file, t_cub3d *a)
{
	calc_map(conf_file, a);
	if (!(a->map.map = (char **)malloc(a->map.row * sizeof(char *))))
		perror("Error\nLa cagaste burt lancaster");
	save_map(conf_file, a);
}

void	init_struct(t_cub3d *a)
{
	a->map.map = NULL;
	a->map.row = 0;
	a->map.col = 0;
}

void	print_map(t_cub3d *a)
{
	int	i;
	
	i = 0;
	printf("row: %d\n", a->map.row);
	printf("colum: %zu\n", a->map.col);
	printf("map[0][7] = %c\n", a->map.map[0][7]);
	while (i < a->map.row)
	{
		printf("linea %d: %s\n", i, a->map.map[i]);
		i++;
	}
	printf("map[0][0] = %c", a->map.map[0][0]);
}

int		main(int argc, char **argv)
{
	t_cub3d	a;

	init_struct(&a);
	if (argc == 2)
	{
		read_map(argv[1], &a);
	}
	else
		perror("Error\nPlease, type carefully, I can'f found the file.\n");
	print_map(&a);//To check if structs saved the data
	system("leaks cub3D");
}
