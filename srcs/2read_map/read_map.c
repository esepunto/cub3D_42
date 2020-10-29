/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/29 23:47:55 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

//static char	**g_map;

void	create_map(int c, char **line, t_all *a)
{
	int 		len;

	if(!(a->conf.map.aux = malloc(sizeof(char*) * 50)))
		return ;
	if(!(a->conf.map.aux[c] = malloc(sizeof(char) * 33)))
		return ;
	if(!(a->conf.map.map = malloc(sizeof(char*) * 50)))
		return ;
	if(!(a->conf.map.map[c] = malloc(sizeof(char) * 33)))
		return ;
	a->conf.map.aux[c] = *line;
	a->conf.map.map[c] = a->conf.map.aux[c];
	len = ft_strlen((const char *)a->conf.map.map[c]);
	write(1, a->conf.map.map[c], len);
	printf("\nlongitud de linea %d = %d\n\n", c, len);

}

int		read_map(char *name_map, t_all *a)
{
	int			fd;
	char		*line;
	int			i;
	static int	c;
//	t_config	config_file;

	if ((fd = open(name_map, O_RDONLY)) == -1)
	{
		perror("Error\n");
		return (0);
	}
	line = NULL;
	c = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
	//	printf("\n%s", line);// >> Manage error and save config in struct
		create_map(c, &line, a);
//		printf("tamaño del line %lu.\n", sizeof(&line));
		free(line);
		line = NULL;
		c++;
	}
//	printf("\n%s", line);
	free(line);
	line = NULL;
	close(fd);
	return (0);
}


int		main(int argc, char **argv)
{
	t_all	a;
	int		i;
//	int		len;

	if (argc == 2)
	{
		read_map(argv[1], &a);
	}
	else
		printf("Please, type carefully. It looks there's an error in you order. Thanks!\n");
//	len = ft_strlen((const char *)a.conf.map.map[1]);
//	printf("linea line lineaaaaa\n%s\n", a.conf.map.map[1]);
//	write(1, a.conf.map.map[1], len);
/*	if (a.conf.map.map != 0)
	{
		while (a.conf.map.map[i])
		{
			len = ft_strlen((const char *)a.conf.map.map[i]);
			write(1, a.conf.map.map[i], len);
			printf("\nlongitud de linea %d = %d\n\n", i, len);
			i++;
		}
	}
*/	i = 0;
	while (a.conf.map.map[i])
	{
		free(a.conf.map.aux[i]);
		free(a.conf.map.map[i]);
		i++;
	}
	free(a.conf.map.aux);
	free(a.conf.map.map);
	a.conf.map.aux = NULL;
	a.conf.map.map = NULL;
	system("leaks cub3D");
}
