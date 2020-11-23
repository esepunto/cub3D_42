/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delinitendblanks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:21:29 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/23 10:23:54 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function returns the string received after deletes the blanks characters
** at the end and the beggining of the string. It deletes spaces and tabs.
*/

char	*ft_delinitendblanks(char *str)
{
	return (ft_delinitblanks(ft_delendblanks(str)));
}
