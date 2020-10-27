/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 21:01:16 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		read_map(char *name_map)
{
	int			fd;
	char		*line;
	int			i;
	
	if ((fd = open(name_map, O_RDONLY)) == -1)
	{
		perror("Error\n");
		return (0);
	}
	line = NULL;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("\n%s", line);// >> Manage error and save config in struct
		free(line);
		line = NULL;
	}
	printf("\n%s", line);
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
