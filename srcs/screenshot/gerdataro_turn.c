/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gerdataro_turn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:06:26 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/05 21:44:12 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	browse_bits(char *header_plus, int i)
{
	header_plus[0] = (unsigned char)i;
	header_plus[1] = (unsigned char)(i >> 8);
	header_plus[2] = (unsigned char)(i >> 16);
	header_plus[3] = (unsigned char)(i >> 24);
}

void	prepare_to_save(int fd, t_cub3d *a, int file_size)
{
	char	header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	browse_bits(header + 2, file_size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	browse_bits(header + 18, a->fconf.xrendersize);
	browse_bits(header + 22, -a->fconf.yrendersize);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)32;
	write(fd, header, 54);
}

void	write_image_to_file(int fd, t_cub3d *a)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)a->mlibx.img.addr;
	while (i < a->fconf.yrendersize)
		write(fd, &tmp[i++ * (a->mlibx.img.line_length * 4)], a->fconf.xrendersize * 16);
}

void	take_photo(t_cub3d *a)
{
	int	fd;
	int	file_size;

	if ((fd = open("./gerda_taro.bmp", O_CREAT | O_RDWR, S_IRWXU)) < 0)
		close_window(a);
	file_size = 54 + (a->fconf.xrendersize * a->fconf.yrendersize * 4);
	prepare_to_save(fd, a, file_size);
	write_image_to_file(fd, a);
	close(fd);
	close_window(a);
}
