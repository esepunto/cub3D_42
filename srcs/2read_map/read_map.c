/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 01:08:03 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		read_map(char *name_map, t_all *a)
{
	int			fd;
	char		*line;
	int			i;
	static int	c;

	
	
	if ((fd = open(name_map, O_RDONLY)) == -1)
	{
		perror("Error\n");
		return (0);
	}
	line = NULL;
	size_t	columnas;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		columnas = ft_strlen(line);
		if (columnas > a->columna_mayor)
			a->columna_mayor = columnas;
		free(line);
		line = NULL;
		a->filas++;
	}
	free(line);
	line = NULL;
	close(fd);


	if (!(a->map = (char **)malloc(a->filas * sizeof(char *))))
		return (-1);
	i = 0;
	if ((fd = open(name_map, O_RDONLY)) == -1)
	{
		perror("Error\n");
		return (0);
	}

	c = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		a->map[c] = ft_strdup(line);
		c++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
	return (0);
}

void	init_struct(t_all *a)
{
	a->map = NULL;
	a->filas = 0;
	a->columna_mayor = 0;
}

int		main(int argc, char **argv)
{
	t_all	a;
	int		i;
	int		len;

	len = 0;
	
	printf("Tamaño estructura antes iniciar: %lu\n", sizeof(t_all));
	init_struct(&a);
	printf("Tamaño estructura antes iniciar: %lu\n", sizeof(a));
	if (argc == 2)
	{
		read_map(argv[1], &a);
	}
	else
		printf("Please, type carefully. It looks there's an error in you order. Thanks!\n");
	printf("filas: %d\n", a.filas);
	printf("colum: %zu\n", a.columna_mayor);
	i = 0;
	printf("map[0][7] = %c\n", a.map[0][7]);
	while (i < a.filas)
	{
		printf("linea %d: %s\n", i, a.map[i]);
		i++;
	}
	printf("map[0][0] = %c", a.map[0][0]);

	i = 0;
/*	if (a.map)
	{
		printf("\nHay a.map.\n");
		while (i < a.filas)
		{
			free(a.map[i]);
			i++;
		}
		free(a.map);
	}
*/	system("leaks cub3D");
}
