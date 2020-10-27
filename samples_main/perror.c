#include "../includes/cub3d.h"

int	main(void)
{
	FILE	*fp;

	fp = fopen("file.txt", "r");
	if (fp == NULL)
	{
		ft_printf("Error: %s\n", strerror(errno));
	}
	system("leaks tutorial");
	return (0);
}
