/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_fconfig.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:57:34 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/06 10:52:38 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	errors_mgmt(char *id, t_cub3d *a, int c)
{
	char		*aux;
//	int			i;
	int			j;
	size_t		len;
	const char	*s2;
	const char	*s1;

	s1 = a->fconf.wallno;
	s2 = id;
	len = ft_strlen((const char *)a->fconf.wallno);

	if (!(aux = ft_strnstr(s1, s2, len)))
		msg_err("Este conf file no me vale");

//	aux = a->fconf.res;
//	i = 0;
	j = a->fconf.init_id[c];
}
