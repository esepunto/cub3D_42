/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/28 13:50:23 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	create_map(int c, char **line)
{
	static int		j;
	int 		len;
//	t_map		map;

	printf("\ntamaño del line %lu.\n", sizeof(line));
	printf("fila %d\n", c);
	printf("%s\n", *line);
	j = 0;
	len = ft_strlen((const char *)*line);
	printf("len = %d\n", len);

//	ft_strdup(*map.map);
//	map.map[j] = *line;
	j++;
/*
	while (j < len)
	{
//		map.map[c][j] = line[c][j];
		map.map[c][j] = '0';
		j++;
	}
*/
}

int		read_map(char *name_map)
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
		create_map(c, &line);
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
	if (argc == 2)
	{
		read_map(argv[1]);
	}
	else
		ft_printf("Please, type carefully. It looks there's an error in you order. Thanks!\n");
	system("leaks cub3D");
}


/*
int		main()
{
//	int	nb = 58;
	int i = 0;
	int j = 0;
	char	*p = MAPA[0];
	p = 0;
	while (i <= 13)
	{
		j = 0;
		while (j <=32)
		{
			ft_printf("%c", MAPA[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
//	printf("%c", MAPA[4][0]);
//	ft_printf("---------------%s,%d", MAPA[12], nb);
//	system("leaks cub3D");
}
*/
