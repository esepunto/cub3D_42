#include "../includes/cub3d.h"


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
	char *s = NULL;

	setbuf(stdout, NULL);


	printf("no_precision return %d|line %d|\n",   printf("|%012d|", INT_MIN), __LINE__);// ERROR
	printf("no_precision return %d|line %d|\n",ft_printf("|%012d|", INT_MIN), __LINE__);
	printf("\n");

	printf("no_precision return %d|line %d|\n",   printf("|%012d|", -2147483000), __LINE__);// ERROR
	printf("no_precision return %d|line %d|\n",ft_printf("|%012d|", -2147483000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",   printf("|%20d|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", INT_MIN), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",   printf("|%20d|", -2147483000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", -2147483000), __LINE__);
	printf("\n");


// return (-1);

	printf("return %d|line %d|\n",printf("|%20d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", -1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", 10), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", 10), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", -1000), __LINE__);//ERROR
	printf("return %d|line %d|\n",ft_printf("|%20d|", -1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", INT_MIN), __LINE__);
	printf("\n");


	printf("return %d|line %d|\n",printf("|%-20d|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", INT_MIN), __LINE__);
	printf("\n");


	printf("return %d|line %d|\n",printf("|%x|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%x|", INT_MIN), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%X|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%X|", INT_MIN), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%u|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%u|", INT_MIN), __LINE__);
	printf("\n");





  //return (-1);

	   printf("|%5c%X%X%X%X%X%x%x%x%x%x0000.%X%X%X%X%X%X%%%*.s.%*.s%%%3.1s%-*.*s%*.3d%x%x%x%x%x%X%X%X%x%x%x%x%x%X%X%X%X%X%-5.x.1_11u.%*.4u.%*.s.%*.s.0.p: %.p.*.s: %*.s.U.%p1011.%*.4d. 101: .%-*u.%-5u.%-5u.Samuel: %c S %5c x.%d.%d.%u.%u.%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p|\n\n", 's', 23,2,46,335,678,456,332,578,5567,42, 74, 453456,3325457,578,5567,42, 4, j, 2, i, NULL, -7, -3, "yolo",12,10, 23,2,46,335,678,456,332,578,5567,42, 45, 1974, 2020, 12315, 135168, 15168, 65673525, 1546, 0, 5, u, 4, j, 2, i, NULL, 32, "hola", &U,7 , -3, 5, 234, -3, 123456, k, m, INT_MAX, INT_MIN, INT_MAX, INT_MIN,&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);
	ft_printf("|%5c%X%X%X%X%X%x%x%x%x%x0000.%X%X%X%X%X%X%%%*.s.%*.s%%%3.1s%-*.*s%*.3d%x%x%x%x%x%X%X%X%x%x%x%x%x%X%X%X%X%X%-5.x.1_11u.%*.4u.%*.s.%*.s.0.p: %.p.*.s: %*.s.U.%p1011.%*.4d. 101: .%-*u.%-5u.%-5u.Samuel: %c S %5c x.%d.%d.%u.%u.%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p%8p|\n\n", 's', 23,2,46,335,678,456,332,578,5567,42, 74, 453456,3325457,578,5567,42, 4, j, 2, i, NULL, -7, -3, "yolo",12,10, 23,2,46,335,678,456,332,578,5567,42, 45, 1974, 2020, 12315, 135168, 15168, 65673525, 1546, 0, 5, u, 4, j, 2, i, NULL, 32, "hola", &U,7 , -3, 5, 234, -3, 123456, k, m, INT_MAX, INT_MIN, INT_MAX, INT_MIN,&a01,&a02,&a03,&a04,&a05,&a06,&a07,&a08,&a09,&a10,&a11,&a12);

	printf("return %d|line %d|\n",printf("|%c|", 'A'), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%c|", 'A'), __LINE__);
	printf("\n");


	printf("return %d|line %d|\n",printf("|%10c|", 'A'), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10c|", 'A'), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*c|", 10, 'A'), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*c|", 10, 'A'), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*c|", -20, 'A'), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*c|", -20, 'A'), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*cHello|", -20, '\0'), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*cHello|", -20, '\0'), __LINE__);

	printf("return %d|line %d|\n",printf("|%%|"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%%|"), __LINE__);


	printf("return %d|line %d|\n",printf("|%s|", "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%s|", "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.s|", "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.s|", "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*.2s|", 10, "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*.2s|", 10, "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*s|", 10, "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*s|", 10, "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*.4s|", 10, "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*.4s|", 10, "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*.40s|", 10, "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*.40s|", 10, "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*.*s|", 10, 15, "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*.*s|", 10, 15, "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*.*s|", 2, 7, "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*.*s|", 2, 7, "Hello"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%s|", s), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%s|", s), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10s|", s), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10s|", s), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.*s|",-50, "Negative precision"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.*s|",-50, "Negative precision"), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-.s|", s), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-.s|", s), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-30s|", "Hello"), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-30s|", "Hello"), __LINE__);



	printf("\n");

		/*
	** Signed integer tests
	*/


	printf("return %d|line %d|\n",printf("|%d|", 10), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", 10), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%d|", -1000), __LINE__);
	printf("\n");


	printf("return %d|line %d|\n",printf("|%20d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20d|", -1000), __LINE__);//ERROR
	printf("return %d|line %d|\n",ft_printf("|%20d|", -1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", -1000), __LINE__);
	printf("\n");



	printf("return %d|line %d|\n",printf("|%020d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%020d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%020d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%020d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%020d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%020d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%020d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%020d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%020d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%020d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%020d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%020d|", -1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.5d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.5d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.5d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.5d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.5d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.5d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.5d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.5d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.5d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.5d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.5d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.5d|", -1000), __LINE__);
	printf("\n");



	printf("return %d|line %d|\n",printf("|%20.30d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.30d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.30d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.30d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.30d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.30d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.30d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.30d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.30d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.30d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.30d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.30d|", -1000), __LINE__);
	printf("\n");


	printf("return %d|line %d|\n",printf("|%.5d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.5d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.5d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.5d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.5d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.5d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.5d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.5d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.5d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.5d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.5d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.5d|", -1000), __LINE__);
	printf("\n");


	printf("return %d|line %d|\n",printf("|%.30d|", INT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.30d|", INT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.30d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.30d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.30d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.30d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.30d|", 1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.30d|", 1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.3d|", 1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.3d|", 1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.3d|", -1000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.3d|", -1000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.d|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%1.d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%1.d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%1.1d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%1.1d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%1.d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%1.d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%2.2d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%2.2d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%2.d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%2.d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.3d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.3d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.2d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.2d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-1.d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-1.d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-1.1d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-1.1d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-1.d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-1.d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-2.2d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-2.2d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-2.d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-2.d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.3d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.3d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.2d|", -1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.2d|", -1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-10.5d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5d|", -216), __LINE__);
	printf("\n");



	/*
	** Negative number, width or precision > number length and left flag on
	*/

	printf("return %d|line %d|\n",printf("|%-10.5d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20.15d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20.15d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-.20d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-.20d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-*.30d|", -21, -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-*.30d|", -21, -216), __LINE__);
	printf("\n");


	/*
	** Negative number, width or precision > number length and left flag off, precision on
	*/

	printf("return %d|line %d|\n",printf("|%15.5d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%15.5d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.15d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.15d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20.4d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20.4d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%*.30d|", 21, -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%*.30d|", 21, -216), __LINE__);
	printf("\n");


	/*
	** Negative number, width  > number length and left flag off, zero flag on
	*/

	printf("return %d|line %d|\n",printf("|%030d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%030d|", -216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%05d|", -216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%05d|", -216), __LINE__);
	printf("\n");

	/*
	** Other %d tests
	*/

	printf("return %d|line %d|\n",printf("|%-10.5d|", 216), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5d|", 216), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-10.5d|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5d|", 0), __LINE__);

	printf("\n");
	printf("MIRAR AHORA!!!!!\n");
printf("\n");


	/*
	** Hex lower %x
	*/

	printf("return %d|line %d|\n",printf("|%x|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%x|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%x|", 9999999), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%x|", 9999999), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20x|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20x|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20x|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20x|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.x|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.5x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.5x|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20x|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20x|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20x|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20x|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-.x|", 99999), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-.x|", 99999), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-10.5x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5x|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%010x|", 16), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%010x|", 16), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-10.0x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.0x|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.0x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.0x|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%010x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%010x|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%010x|", 42), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%010x|", 42), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.x|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.x|", 0), __LINE__);
	printf("\n");


	/*
	** Hex upper %X
	*/

	printf("return %d|line %d|\n",printf("|%X|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%X|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%X|", 9999999), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%X|", 9999999), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20X|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20X|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20X|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20X|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.X|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.X|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.5X|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.5X|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20X|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20X|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20X|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20X|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-.X|", 99999), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-.X|", 99999), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-10.5X|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5X|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%010X|", 16), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%010X|", 16), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.X|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.X|", 0), __LINE__);
	printf("\n");


	/*
	** Unsigned integer tests %u
	*/

	printf("return %d|line %d|\n",printf("|%u|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%u|", UINT_MAX), __LINE__);
	printf("\n");



	printf("return %d|line %d|\n",printf("|%u|", 9999999), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%u|", 9999999), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20u|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20u|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20u|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20u|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.u|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.u|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.5u|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.5u|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20u|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20u|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.20u|", UINT_MAX), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.20u|", UINT_MAX), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-.u|", 99999), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-.u|", 99999), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-10.5u|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-10.5u|", 0), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%010u|", 16), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%010u|", 16), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%10.u|", 0), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%10.u|", 0), __LINE__);
	printf("\n");



	/*
	** Pointer testing %p
	**
	** Every time a variable is declared will be assigned
	** in a different memory place.
	** Comparing this conversion with diff will differ always
	*/


	char	*p1;
	char	**p2;
	char	***p3;
	char	zz;

	zz = 'Z';
	p1 = &zz;
	p2 = &p1;
	p3 = &p2;
	printf("return %d|line %d|\n",printf("|%p|", p1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%p|", p1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%p|", p1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%p|", p1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%p|", p2), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%p|", p2), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%p|", p3), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%p|", p3), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20p|", p1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20p|", p1), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20p|", p1), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20p|", p1), __LINE__);
	printf("\n");


	/*
	** Pointer testing, NULL pointer
	*/

	char	********************************************p4;
	p4 = NULL;
	printf("return %d|line %d|\n",printf("|%p|", p4), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%p|", p4), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%20p|", p4), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%20p|", p4), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%2p|", p4), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%2p|", p4), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%-20p|", p4), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%-20p|", p4), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%p|", p4), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%p|", p4), __LINE__);
	printf("\n");


	/*
	** %n Bonus
	*/

	/*
	int a;
	int b;
	printf("return %d|line %d|\n",printf("|Hello%n World!|", &b), __LINE__);
	printf("return %d|line %d|\n",printf("|Hello%n World!|", &b), __LINE__);

	printf("return %d|line %d|\n",F("%%n = %d", b), __LINE__);

	printf("return %d|line %d|\n",printf("|Hello%n World!%n!|", &b, &a), __LINE__);

	printf("return %d|line %d|\n",F("%%n = %d", b), __LINE__);

	printf("return %d|line %d|\n",F("%%n = %d", a), __LINE__);

	printf("return %d|line %d|\n",F("%n", &b), __LINE__);

	printf("return %d|line %d|\n",F("%%n = %d", b), __LINE__);

	printf("return %d|line %d|\n",F("%n\\", &b), __LINE__);

	printf("return %d|line %d|\n",F("%%n = %d", b), __LINE__);
	*/

	/*
	** Undefined behaviour
	*/

	/*
	printf("return %d|line %d|\n",F("%"), __LINE__);
	printf("return %d|line %d|\n",F("%m%r"), __LINE__);
	printf("return %d|line %d|\n",F("%m%r%52"), __LINE__);
	printf("return %d|line %d|\n",F("% %"), __LINE__);
	printf("return %d|line %d|\n",F("% %"), __LINE__);
	*/

	/*
	** CASOS YA REVISADOS Y OK
	** COMPROBAR ANTES DE SUBIR A LA MOULI
	*/

	printf("return %d|line %d|\n",printf("|%12.5d|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%12.5d|", INT_MIN), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%2.5d|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%2.5d|", INT_MIN), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.2d|", INT_MIN), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.2d|", INT_MIN), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%12.5d|", -2147483000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%12.5d|", -2147483000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%2.5d|", -2147483000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%2.5d|", -2147483000), __LINE__);
	printf("\n");

	printf("return %d|line %d|\n",printf("|%.2d|", -2147483000), __LINE__);
	printf("return %d|line %d|\n",ft_printf("|%.2d|", -2147483000), __LINE__);
	printf("\n");



	printf("_precision return %d|line %d|\n",   printf("|%12.30d|", INT_MIN), __LINE__);// ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%12.30d|", INT_MIN), __LINE__);
	printf("\n");

	printf("_precision return %d|line %d|\n",   printf("|%12.30d|", -2147483000), __LINE__);// ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%12.30d|", -2147483000), __LINE__);
	printf("\n");

	printf("_precision return %d|line %d|\n",   printf("|%2.30d|", INT_MIN), __LINE__);//ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%2.30d|", INT_MIN), __LINE__);
	printf("\n");



	printf("_precision return %d|line %d|\n",   printf("|%-30.15d|", INT_MIN), __LINE__);// ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%-30.15d|", INT_MIN), __LINE__);
	printf("\n");

	printf("_precision return %d|line %d|\n",   printf("|%-30.15d|", -2147483000), __LINE__);// ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%-30.15d|", -2147483000), __LINE__);
	printf("\n");

		printf("_precision return %d|line %d|\n",   printf("|%030.15d|", INT_MIN), __LINE__);// ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%030.15d|", INT_MIN), __LINE__);
	printf("\n");

	printf("_precision return %d|line %d|\n",   printf("|%-30.15d|", -2147483000), __LINE__);// ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%-30.15d|", -2147483000), __LINE__);
	printf("\n");

	printf("_precision return %d|line %d|\n",   printf("|%-30.15d|", INT_MIN), __LINE__);//ERROR
	printf("_precision return %d|line %d|\n",ft_printf("|%-30.15d|", INT_MIN), __LINE__);
	printf("\n");

	return (0);
}
