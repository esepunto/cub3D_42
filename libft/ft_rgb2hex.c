/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb2hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:51:47 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/02 10:54:08 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		calculate_hex(int c, int color, char *result)
{
	if (c % 2 == 0)
		result[c] = HEXADEC[color / 16];
	else
		result[c] = HEXADEC[color % 16];
}

char		*ft_rgb2hex(int r, int g, int b)
{
	static char	result[6];
	int			i;
	char		*aux;
	char		*val;

	i = 0;
	while (i < 6)
	{
		if (i < 2)
			calculate_hex(i, r, result);
		else if (i < 4)
			calculate_hex(i, g, result);
		else
			calculate_hex(i, b, result);
		i++;
	}
	aux = ft_strjoin("0x00\0", result);
	val = aux;
	free(aux);
	return (val);
}
