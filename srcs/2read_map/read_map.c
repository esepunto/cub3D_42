/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:07:43 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 18:16:53 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		main(int argc, char **argv)
{
	if (argc = 2)
	{
		read_map(argv[1]);	
	}
	else
		return (-1);
}

char	read_map(char *name_map)
{
	int			fd;
	char		*line;
	int			i;
	t_config	cubconf;
	
	line = NULL;
	fd = open(name_map, O_RDONLY);
	while ((i = get_next_line(fd, &line)) == 1)
	{
		printf("\n%s", line);
		line = NULL;
		free(line);
	}
	if ((i = get_next_line(fd, &line)) == 0)
	{
		printf("\n%s", line);
		line = NULL;
		free(line);
	}
	close(fd);
	system("leaks a.out");
	return (0);
}
