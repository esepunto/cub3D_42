/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:29:49 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/27 11:46:18 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **a)
{
	if (!a || !*a)
		return ;
	free(*a);
	*a = NULL;
}

char	*ft_extract(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	if (!(temp = malloc(ft_strlen(str) + 1)))
		return (NULL);
	while (*str != '\n')
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

int		ft_chop(char **str, char **line)
{
	char	*temp;

	if (*str && ft_strchr(*str, '\n') > 0)
	{
		temp = ft_strchr(*str, '\n') + 1;
		temp = ft_strdup(temp);
		*line = ft_extract(*str);
		ft_memdel((void **)str);
		*str = temp;
		return (1);
	}
	if (*str != 0)
		*line = ft_strdup(*str);
	else
		*line = ft_strdup("");
	ft_memdel((void **)str);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			bytes_buf;
	char		*buffer;
	static char	*dest[4096];
	char		*aux;

	if (!(buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || fd < 0
						|| !line || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	while ((bytes_buf = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_buf] = '\0';
		if (!dest[fd])
			dest[fd] = ft_strdup(buffer);
		else
		{
			aux = ft_strjoin(dest[fd], buffer);
			ft_memdel((void **)&dest[fd]);
			dest[fd] = aux;
		}
		if (ft_strchr(dest[fd], '\n'))
			break ;
	}
	ft_memdel((void **)&buffer);
	return (ft_chop(&dest[fd], line));
}
