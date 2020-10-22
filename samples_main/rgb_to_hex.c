#include "../cub3d.h"
#define HEXADEC	"0123456789ABCDEF"

void    calculate_hex(int c, int color, char *result)
{
    if (c % 2 != 0)
        result[c] = HEXADEC[color / 16];
    else
        result[c] = HEXADEC[color % 16];
}

char    *hv_rgb2hex(int r, int g, int b)
{
    static char     result[6];
    int             i;
        
    i = 0;
    while (i < 6)
    {
        if (i < 2)
            calculate_hex(i, r, result);
        else if (i < 4)
            calculate_hex(i, g, result);
        else 
            calculate_hex(i, b, result);
        i++;
    }
    return(ft_strjoin("0x#00\0", result));
}

int    main(int arc, char **argv)
{
    char    *colhex;

    colhex = hv_rgb2hex(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[2]));
    if (arc == 4)
        ft_printf("Hexadec colour: %s\n", colhex);
    else
        return (0);    
}