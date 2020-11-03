/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/03 14:46:54 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
void	create_map(int c, char **line, t_all *a)
{
	int 		len;
	t_all		aux;

	if(!(a->map = malloc(sizeof(char*) * 24)))
		return ;
	if(!(a->map[c] = malloc(sizeof(char) * 33)))
		return ;
	if(!(aux.map = malloc(sizeof(char*) * 24)))
		return ;
	if(!(aux.map[c] = malloc(sizeof(char) * 33)))
		return ;
	aux.map[c] = *line;
	a->map[c] = aux.map[c];

//	ft_strjoin(lo que tenía, line)
//	ft_split(ft_stroin)

//	aux.map[c] = NULL;
	len = ft_strlen((const char *)a->map[c]);
	write(1, a->map[c], len);
	printf("\nlen line %d = %d\n\n", c, len);
	free(aux.map);
}
*/

int		read_map(char *name_map, t_all *a)
{
	int			fd;
	char		*line;
	int			i;
	static int	c;
	t_all		aux;

	aux = *a;
	if ((fd = open(name_map, O_RDONLY)) == -1)
	{
		perror("Error\n");
		return (0);
	}
	line = NULL;
	c = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
//		create_map(c, &line, a);
		if (!a->map)
			a->map = ft_strdup(line);
		aux.map = ft_strjoin((const char *)a->map, line);
		free(&a->map);
		a->map = aux.map;
		free(line);
		line = NULL;
		c++;
	}
	free(line);
	line = NULL;
	a->map = *ft_split(a->map, '\n');
	printf("%s", a->map);
	close(fd);
	return (0);
}

void	init_struct(t_all *a)
{
//	a->conf = (t_config)NULL;
//	a->raycast = (t_rayc)NULL;
	a->map = NULL;

}

int		main(int argc, char **argv)
{
	t_all	a;
	int		i;
	int		len;

	len = 0;

	init_struct(&a);
	if (argc == 2)
	{
		read_map(argv[1], &a);
	}
	else
		printf("Please, type carefully. It looks there's an error in you order. Thanks!\n");
	i = 0;
/*	while (i <= 23)
	{
		free(a.map[i]);
		a.map[i] = NULL;
		i++;
	}
	free(a.map);
	a.map = NULL;
*/	printf("%s", a.map);
	free(a.map);
	system("leaks cub3D");
}
