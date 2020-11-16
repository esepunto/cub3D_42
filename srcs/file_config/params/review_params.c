/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:35 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/16 13:29:36 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/*
** The info of any param is at a->fconf.wall_texture[c], where
** 'c' is a var that corresponds to:
**  _______________________________
**	|  param    | c |   element   |
**	|___________|___|_____________|
**	|   "NO"    | 0 |    north    |
**	|   "SO"    | 1 |    south    |
**  |	"WE"    | 2 |    west     |
**	|	"EA"    | 3 |    east     |
**	|	"R"     | 4 |  resolution |
**	|	"C"     | 5 |  ceilling   |
**	|	"F"     | 6 |    floor    |
**	|	"S"     | 7 |   sprites   |
**  |___________|___|_____________|
*/

/*
int	ft_count_wrds(int c, t_cub3d *a)//Review to put in on libft
{
	int	len;
	int	i;
	int	count;

	count = 0;
	len = ft_strlen(a->fconf.wall_texture[c]);
	i = 0;
	while (i <= len)
	{
		while(ft_isblank(a->fconf.wall_texture[c][i]))
			i++;
		if(ft_isprint(a->fconf.wall_texture[c][i]) && !ft_isblank(a->fconf.wall_texture[c][i]))
			count++;
		i++;
		while (ft_isprint(a->fconf.wall_texture[c][i]) && !ft_isblank(a->fconf.wall_texture[c][i]))
			i++;
		i++;
	}
	return (count);
}
*/

int		ft_count_wrds(int c, t_cub3d *a)
{
	size_t	i;
	int		count;
	char	*s;

	i = 0;
	count = 0;
	s = a->fconf.wall_texture[c];
	while (s[i])
	{
		if (!ft_isblank(s[i]))
			count++;
		while (s[i] != ' ' && s[i + 1])
			i++;
		i++;
	}
	return (count);
}


char	*del_last_spaces(char *str)
{
	size_t	len;
	size_t	c;

	len = ft_strlen(str);
	c = len;
	while (c > 1)
	{
		if (ft_isblank(str[c]))
			str[c] = '\0';
		c--;
	}
	return (str);
}

/*
** Next 3 functions check the number os params in:
** 		a) walls and sprites
** 		b) floor and ceilling
** 		c) resolution
*/

void	review_walls(int c, t_cub3d *a)
{
	int	fd;//Check to put in on struct

	int	len = ft_strlen(a->fconf.wall_texture[c]);//To deleted last space add at the end of the program
	a->fconf.wall_texture[c][len - 1] = '\0';//To deleted last space add at the end of the program
	if (ft_count_wrds(c, a) != 1)
	{
//		printf("textura error %s", a->fconf.wall_texture[c]);
		msg_err("Too much information in walls.");
	}
	a->fconf.wall_texture[c] = del_last_spaces(a->fconf.wall_texture[c]);
	if (ft_chekext(a->fconf.wall_texture[c], ".png") != 0)
		msg_err("Bad extension in textures.");
	if ((fd = open(a->fconf.wall_texture[c], O_RDONLY)) == -1)
	{
		printf("|%s|\n", a->fconf.wall_texture[c]);
		msg_err("This file is out of the air.");
	}
	else
		close(fd);
}

void	look4rgb(int c, t_cub3d *a)
{
	size_t	j;
	size_t	len;
//	int		red;
	const char	*r;
	int		green;
	int		blue;
	char	*aux;
	int		h;
	static int	count;


	if (!count)
		count = 0;
	blue = 0;
	green = 0;
	aux = a->fconf.wall_texture[c];
	len = ft_strlen(aux);
	j = 0;
	while (j <= len)
	{
		while (ft_isdigit(aux[j]))
			j++;
		r = ft_substr((const char *)aux, 0, j);
		a->fconf.red[count] = ft_atoi(r);
		free((void *)r);
//		j++;


		while (ft_isblank(aux[j]))
			j++;
		if (aux[j] != ',')
			msg_err("Bad separations 0.");
		j++;
		h = j;
		while (ft_isdigit(aux[j]))
			j++;
		r = ft_substr((const char *)aux, h, j);
		a->fconf.green[count] = ft_atoi(r);
		free((void *)r);
//		j++;

		while (ft_isblank(aux[j]))
			j++;
		if (aux[j] != ',')
			msg_err("Bad separations 1.");
		j++;
		h = j;
		while (ft_isdigit(aux[j]))
			j++;
		r = ft_substr((const char *)aux, h, j);
		a->fconf.blue[count] = ft_atoi(r);
		free((void *)r);

		count++;
		break ;
	}
}

void	review_cefl(int c, t_cub3d *a)
{
	if (ft_count_wrds(c, a) < 1 || ft_count_wrds(c, a) > 3)
		msg_err("Bad floor/ceilling elements.");
	look4rgb(c, a);
}

void	review_res(int c, t_cub3d *a)
{
	if (ft_count_wrds(c, a) != 2)
		msg_err("Poor information in resolution.");
}

void	review_params(t_cub3d *a)
{
	int		c;

	c = 0;
	while (c <= 7)
	{
		if (c < 4 || c == 7)
			review_walls(c, a);
		if (c >= 5 && c <= 6)
			review_cefl(c, a);
		if (c == 4)
			review_res(c, a);
		c++;
	}
}
