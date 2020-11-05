/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_fconfig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:57:34 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/05 18:57:34 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	errors_mgmt(char *id, t_cub3d *a, int c)
{
	char	*aux;
	int		i;
	int		j;

	a->fconf.wallno = (look4_id("NO ", a, 0));
	
	aux = a->fconf.res;
	i = 0;
	j = a->fconf.init_id[c];
}