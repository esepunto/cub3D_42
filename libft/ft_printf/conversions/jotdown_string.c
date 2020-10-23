/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jotdown_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:46:57 by ssacrist          #+#    #+#             */
/*   Updated: 2020/10/23 11:02:32 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

void	jotdown_s(t_format *carrier)
{
	char	*arg;

//	flag(carrier->flagstr, 0, carrier);
	flag((*carrier).flagstr, 0, carrier);
	adjust_flags_s(carrier);
	arg = va_arg(carrier->arguments, char *);
	if (arg == NULL)
		arg = "(null)";
//	carrier->large_arg = ft_strlen(arg);
	(*carrier).large_arg = ft_strlen(arg);
//	print_s(arg, carrier);
	print_s(arg, &(*carrier));
}

void	print_s(char *arg, t_format *carrier)
{
	if (carrier->minus == 1)
		ft_putstr(arg, carrier);
	if (carrier->precision >= carrier->large_arg || carrier->precision < 0)
		writespaces(carrier->width - carrier->large_arg, carrier);
	else if (carrier->precision >= 0)
		writespaces(carrier->width - carrier->precision, carrier);
	if (carrier->minus == 0)
		ft_putstr(arg, carrier);
}
