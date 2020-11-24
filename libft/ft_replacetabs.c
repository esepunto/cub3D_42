/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replacetabs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 08:14:17 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/24 08:15:18 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replace tabs by spaces
*/

char	*ft_replacetabs(char *str)
{
	size_t	c;

	c = 0;
	while (c <= ft_strlen(str))
	{
		if (str[c] == '	')
			str[c] = ' ';
		c++;
	}
	return (str);
}
