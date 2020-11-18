/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lastblanks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:21:18 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/18 12:24:07 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function returns the strinf received after deletes the blanks characters
** at the end of the string. It deletes spaces and tabs.
*/

char	*ft_lastblanks(char *str)
{
	size_t	len;
	size_t	c;

	len = ft_strlen(str);
	c = len;
	while (c > 1)
	{
		if (ft_isblank(str[c]))
			str[c] = '\0';
		c--;
	}
	return (str);
}
