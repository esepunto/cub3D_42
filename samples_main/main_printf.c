/*
 * To compile: gcc -Wall -Wextra -Werror main.c libftprintf.a && ./a.out
*/

#include "../cub3d.h"
#include <limits.h>

int		main()
{	
	char	*j = "Samuel";
	char	*i = "Sandra";
	char	k = 'T';
	char	m = 'b';
	unsigned int	u = 0;
	unsigned int	U = 4294967295;
	int	a01 = 1;
	int	a02 = 1;
	int	a03 = 1;
	int	a04 = 1;
	int	a05 = 1;
	int	a06 = 1;
	int	a07 = 1;
	int	a08 = 1;
	int	a09 = 1;
	int	a10 = 1;
	int	a11 = 1;
	int	a12 = 1;
	
	   printf("|%5c%X%X%X%X%X%x%x%x%x%x0000.%X%X%X%X%X%X%%%*.s.%*.s%%%3.1s%-*.*s%*.3d%x%x%x%x%x%X%X%X%x%x%x%x%x%X%X%X%X%X%-5.x.1_11u.%*.4u.%*.s.%*.s.0.: %.p.*.s: %*.s.U.%p1011.%*.4d. 101: .%-*u.%-5u.%-5u.Samuel: %c S %5c x.%d.%d.%u.%u.%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p|\n\n", 's', 23,2,46,335,678,456,332,578,5567,42, 74, 453456,3325457,578,5567,42, 4, j, 2, i, NULL, -7, -3, "yolo",12,10, 23,2,46,335,678,456,332,578,5567,42, 45, 1974, 2020, 12315, 135168, 15168, 65673525, 1546, 0, 5, u, 4, j, 2, i, NULL, 32, "hola", &U,7 , -3, 5, 234, -3, 123456, k, m, INT_MAX, INT_MIN, INT_MAX, INT_MIN,&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12); 
	ft_printf("|%5c%X%X%X%X%X%x%x%x%x%x0000.%X%X%X%X%X%X%%%*.s.%*.s%%%3.1s%-*.*s%*.3d%x%x%x%x%x%X%X%X%x%x%x%x%x%X%X%X%X%X%-5.x.1_11u.%*.4u.%*.s.%*.s.0.: %.p.*.s: %*.s.U.%p1011.%*.4d. 101: .%-*u.%-5u.%-5u.Samuel: %c S %5c x.%d.%d.%u.%u.%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p|\n\n", 's', 23,2,46,335,678,456,332,578,5567,42, 74, 453456,3325457,578,5567,42, 4, j, 2, i, NULL, -7, -3, "yolo",12,10, 23,2,46,335,678,456,332,578,5567,42, 45, 1974, 2020, 12315, 135168, 15168, 65673525, 1546, 0, 5, u, 4, j, 2, i, NULL, 32, "hola", &U,7 , -3, 5, 234, -3, 123456, k, m, INT_MAX, INT_MIN, INT_MAX, INT_MIN,&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);
	printf("\n");
}
