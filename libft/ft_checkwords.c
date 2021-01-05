/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:26:47 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/05 18:56:54 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  This function receives two strings and corpare its. If return 0, the
**  two words are equal.
*/

int		ft_checkwords(const char *str1, const char *str2)
{
	int		str1len;
	int		str2len;

	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	if (str1len != str2len)
		return (1);
	return (ft_memcmp(str1, str2, str1len));
}
