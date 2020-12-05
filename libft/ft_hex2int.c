/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex2int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:27:01 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/05 10:20:30 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Take a hex string and convert it to a 32bit number (max 8 hex digits)
**
** 1. Get current character then increment (line 32).
** 2. Transform hex character to the 4bit equivalent number, using
**      the ascii table indexes (lines 34 - 39).
** 3. Shift 4 to make space for new digit, and
**      add the 4 bits of the new digit (line 41).
*/

uint32_t	ft_hex2int(char *hex)
{
	uint32_t	val;
	uint8_t		byte;

	val = 0;
	while (*hex)
	{
		byte = *hex++;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		val = (val << 4) | (byte & 0xF);
	}
	return (val);
}
