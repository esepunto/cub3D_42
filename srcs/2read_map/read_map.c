/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 07:59:26 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		read_map(char *name_map, t_cub3d *a)
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
		if (columnas > a->map.columna_mayor)
			a->map.columna_mayor = columnas;
		free(line);
		line = NULL;
		a->map.filas++;
	}
	free(line);
	line = NULL;
	close(fd);


	if (!(a->map.map = (char **)malloc(a->map.filas * sizeof(char *))))
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
		a->map.map[c] = ft_strdup(line);
		c++;
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd);
	return (0);
}

void	init_struct(t_cub3d *a)
{
	a->map.map = NULL;
	a->map.filas = 0;
	a->map.columna_mayor = 0;
}

int		main(int argc, char **argv)
{
	t_cub3d	a;
	int		i;
	int		len;

	len = 0;
	
	printf("Tamaño estructura antes iniciar: %lu\n", sizeof(t_cub3d));
	init_struct(&a);
	printf("Tamaño estructura antes iniciar: %lu\n", sizeof(a));
	if (argc == 2)
	{
		read_map(argv[1], &a);
	}
	else
		printf("Please, type carefully. It looks there's an error in you order. Thanks!\n");
	printf("filas: %d\n", a.map.filas);
	printf("colum: %zu\n", a.map.columna_mayor);
	i = 0;
	printf("map[0][7] = %c\n", a.map.map[0][7]);
	while (i < a.map.filas)
	{
		printf("linea %d: %s\n", i, a.map.map[i]);
		i++;
	}
	printf("map[0][0] = %c", a.map.map[0][0]);

	i = 0;
/*	if (a.map.map)
	{
		printf("\nHay a.map.map.\n");
		while (i < a.map.filas)
		{
			free(a.map.map[i]);
			i++;
		}
		free(a.map.map);
	}
*/	system("leaks cub3D");
}
