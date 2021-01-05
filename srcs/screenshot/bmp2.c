/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:06:26 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/05 17:32:38 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	prepare_to_save(int fd, t_cub3d *a, int tmp, int file_size)
{
	char	header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	header[2] = (unsigned char)file_size;
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	header[18] = (unsigned char)tmp;
	header[19] = (unsigned char)(tmp >> 8);
	header[20] = (unsigned char)(tmp >> 16);
	header[21] = (unsigned char)(tmp >> 24);
	tmp = -a->mlibx.sizex;
	header[22] = (unsigned char)tmp;
	header[23] = (unsigned char)(tmp >> 8);
	header[24] = (unsigned char)(tmp >> 16);
	header[25] = (unsigned char)(tmp >> 24);
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
	while (i < a->mlibx.sizey)
		write(fd, &tmp[i++ * (a->mlibx.img.line_length * 4)], a->mlibx.sizex * 4);
}

void	take_screenshot(t_cub3d *a)
{
	int	fd;
	int	tmp;
	int	file_size;

	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR, S_IRWXU)) < 0)
		close_window(a);
	tmp = a->mlibx.sizex;
	file_size = 14 + 40 + (a->mlibx.sizex * a->mlibx.sizey) * 4;
	prepare_to_save(fd, a, tmp, file_size);
	write_image_to_file(fd, a);
	close(fd);
	close_window(a);
}
