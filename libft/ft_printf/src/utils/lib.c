/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:39:59 by ssacrist          #+#    #+#             */
/*   Updated: 2020/07/22 19:40:13 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libftprintf.h"

char	*ft_itoa_u(unsigned int n)
{
	long	nbr;
	size_t	len;
	char	*str;

	nbr = n;
	len = (nbr > 0) ? 0 : 1;
	nbr = (nbr > 0) ? nbr : -nbr;
	while (n)
		n = len++ ? n / 10 : n / 10;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	if (len == 0 && str[1] != '\0')
		*(str + len) = '-';
	return (str);
}
