/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delendblanks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:21:18 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/24 08:51:51 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function returns the strinf received after deletes the blanks characters
** at the end of the string. It deletes spaces and tabs.
*/

char	*ft_delendblanks(char *str)
{
	size_t	len;
	size_t	c;

	len = ft_strlen(str);
	c = len - 1;
	while (c > 1 && ft_isblank(str[c]))
	{
		str[c] = '\0';
		c--;
	}
	return (str);
}
