/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntwrds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:06:56 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/18 12:10:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** To count the number of "words" in a string.
** "words" = any string of chars (excepts blank chars)
**
** Danger! It counts special chars. not only print chars.
*/

size_t	ft_cntwrds(char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_isblank(str[i]))
			count++;
		while (str[i] != ' ' && str[i + 1])
			i++;
		i++;
	}
	return (count);
}
