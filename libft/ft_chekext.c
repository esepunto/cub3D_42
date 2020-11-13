/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chekext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:10:10 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/13 14:18:37 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  This function receives a string and an extension, and
**  checks if string ends with this extension. If return != 0, the
**  file extesion is bad.
*/

int		ft_chekext(const char *str, char *ext)
{
	int		strlen;
	int		extlen;

	strlen = ft_strlen(str);
	extlen = ft_strlen(ext);
	return (ft_memcmp(str + strlen - extlen, ext, extlen));
}
