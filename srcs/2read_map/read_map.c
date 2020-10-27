/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 20:32:14 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		read_map(char *name_map);

int		main(int argc, char **argv)
{
	if (argc == 2)
	{
		read_map(argv[1]);	
	}
	system("leaks cub3D");
}

int		read_map(char *name_map)
{
	int			fd;
	char		*line;
	int			i;
	//t_config	cubconf;
	
	if ((fd = open(name_map, O_RDONLY)) == -1)
	{
		printf("Error: %s\n", strerror(errno));
		return (0);
	}
	line = NULL;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("\n%s", line);
		free(line);
		line = NULL;
	}
	printf("\n%s", line);
	free(line);
	line = NULL;
	close(fd);
	return (0);
}
