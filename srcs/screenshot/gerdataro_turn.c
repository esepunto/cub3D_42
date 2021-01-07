/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gerdataro_turn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:06:26 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/07 13:18:30 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** See comments below (at the lower of).
*/

void	browse_bits(char *header_plus, int i)
{
	header_plus[0] = (unsigned char)i;
	header_plus[1] = (unsigned char)(i >> 8);
	header_plus[2] = (unsigned char)(i >> 16);
	header_plus[3] = (unsigned char)(i >> 24);
}

/*
** header[0] = 0x42, so, please, excuse the joke in line 36 (or don't)
*/

void	write_header(int fd, t_cub3d *a, int file_size)
{
	char	header[54];

	ft_bzero(header, 54);
	header[0] = Answer_to_the_Ultimate_Question_of_Life;
	header[1] = 0x4D;
	browse_bits(header + 2, file_size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	browse_bits(header + 18, a->fconf.xrendersize);
	browse_bits(header + 22, -a->fconf.yrendersize);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)32;
	write(fd, header, 54);
}

void	write_image(int fd, t_cub3d *a)
{
	char	*pixels_from_image;
	int		i;

	i = 0;
	pixels_from_image = (char *)a->mlibx.img.addr;
	while (i < a->fconf.yrendersize)
		write(fd,
			&pixels_from_image[i++ * (a->mlibx.img.line_length * 4)],
			a->fconf.xrendersize * 16);
}

void	take_photo(t_cub3d *a)
{
	int	fd;
	int	file_size;

	if ((fd = open("./gerda_taro.bmp", O_CREAT | O_RDWR, S_IRWXU)) < 0)
		msg_err("I can't create the file.");
	file_size = 54 + (a->fconf.xrendersize * a->fconf.yrendersize * 4);
	write_header(fd, a, file_size);
	write_image(fd, a);
	close(fd);
	close_window(a);
}

/*
** BMP file has the following format:
** 
** Header: 54 bytes
** Palette (optional): 0 bytes (for 24-bit RGB images)
** Image Data: file size - 54 bytes (for 24-bit RGB images)
**
** METADATA OF BMP HEADER (labeled BITMAPFILEHEADER). Total: 14 bytes (0-13).
**
** FileType (2 bytes). A 2 character string value in ASCII to specify a
** DIB file type. It must be 'BM' or '0x42 0x4D' in hexadecimals for modern
** compatibility reasons.
**
** FileSize (4 bytes). An integer (unsigned) representing entire file size in
** bytes. This value is basically the number of bytes in a BMP image file.
**
** Reserved (2 bytes). These 2 bytes are reserved to be utilized by an image
** processing application to add additional meaningful information. It should
** be initialized to '0' integer (unsigned) value.
**
** Reserved (2 bytes). Same as the above.
**
** PixelDataOffset (4 bytes). An integer (unsigned) representing the offset
** of actual pixel data in bytes. In nutshell:- it is the number of bytes
** between start of the file (0) and the first byte of the pixel data.
**
** 
** INFODATA OF DIB HEADER (labeled BITMAPINFOHEADER). Total: 40 bytes (14-54)
** 
** HeaderSize (4 bytes). An integer (unsigned) representing the size of the
** header in bytes. It should be '40' in decimal to represent
** BITMAPINFOHEADER header type.
**
** ImageWidth (4 bytes). An integer (signed) representing the width of the
** final image in pixels.
**
** ImageHeight (4 bytes). An integer (signed) representing the height of the 
** final image in pixels.
**
** Planes (2 bytes). An integer (unsigned) representing the number of color
** planes of the target device. Should be '1' in decimal.
**
** BitsPerPixel (2 bytes). An integer (unsigned) representing the number of
** bits (memory) a pixel takes (in pixel data) to represent a color.
**
** Compression (4 bytes). An integer (unsigned) representing the value of
** compression to use. Should be '0' in decimal to represent no-compression
** (identified by 'BI_RGB'). NOT USE IN THIS HEADER.
**
** ImageSize (4 bytes). An integer (unsigned) representing the final size
** of the compressed image. Should be '0' in decimal when no compression
** algorithm is used. NOT USE IN THIS HEADER.
**
** XpixelsPerMeter (4 bytes). An integer (signed) representing the horizontal
** resolution of the target device. This parameter will be adjusted by the
** image processing application but should be set to '0' in decimal to
** indicate no preference. NOT USE IN THIS HEADER.
**
** YpixelsPerMeter (4 bytes). An integer (signed) representing the verical
** resolution of the target device (same as the above). NOT USE IN THIS HEADER.
**
** TotalColors (4 bytes). An integer (unsigned) representing the number of
** colors in the color pallet (size of the color pallet or color table). If
** this is set to '0' in decimal :- 2^BitsPerPixel colors are used. NOT USE.
**
** ImportantColors (4 bytes). An integer (unsigned) representing the number of
** important colors. Generally ignored by setting '0' decimal value. NOT USE.
**
** Link with info about BMP: https://engineering.purdue.edu/ece264/17au/hw/HW15
*/
