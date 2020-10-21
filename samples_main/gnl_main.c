#include "../cub3d.h"

int
		main(void)
{
	int		r;
	char	*line;
	
	line = NULL;
	while ((r = get_next_line(0, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
	system("leaks tutorial");
}