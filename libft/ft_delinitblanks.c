/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delinitblanks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:21:18 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 09:04:00 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function returns the string received after deletes the blanks characters
** at the end of the string. It deletes spaces and tabs.
*/

char	*ft_delinitblanks(char *str)
{
	while (ft_isblank(*str))
		str++;
	return (str);
}
