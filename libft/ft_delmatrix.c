/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delmatrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:42:06 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/31 09:11:47 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delmatrix(char **matrix)
{
	int c;

	c = 0;
	while (matrix[c])
	{
		free(matrix[c]);
		c++;
	}
	free(matrix);
}
