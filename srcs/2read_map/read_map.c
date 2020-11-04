/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/04 07:52:51 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		else
		{	
			aux.map = ft_strjoin(a->map, line);
			free(a->map);
			a->map = aux.map;
		}
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
