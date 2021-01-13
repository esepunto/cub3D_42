#include "includes/cub3d.h"

void		print_sprites(t_cub3d *a)
{
	int	c;
	static int i = 1;
	
	
	c = 0;
	//printf("distance[%d]: %f\n", a->rayc.nbr_ray, a->rayc.alldistances[a->rayc.nbr_ray]);
	while (c < a->fconf.map.nbr_sprite)
	{
		int h = 0;
		printf("sprite[%d]     xpos: |%d|\n",c, a->sprite[c].xpos);
		printf("sprite[%d]     ypos: |%d|\n",c,a->sprite[c].ypos);
		printf("sprite[%d]   yfloat: |%f|\n",c, a->sprite[c].yfloat);
		printf("sprite[%d]    ystep: |%f|\n",c, a->sprite[c].ystep);
		printf("sprite[%d] midangle: |%f|\n",c, a->sprite[c].midangle);
		while (h < a->fconf.xrendersize)
		{
			if (a->sprite[c].buff[h].ray == 1)
			{
				printf("sprite[%d]_ray[%d]     used: |%d|\n",c, h, a->sprite[c].buff[h].ray);
				printf("sprite[%d]          midangle: |%f|\n",c, a->sprite[c].midangle);
				printf("sprite[%d]_ray[%d]    angle: |%f|\n",c, h, a->sprite[c].buff[h].angle);
			}
			h++;
		}
/*		printf("sprite[%d] sequence: |%d|\n",c, a->sprite[c].sequence);
		printf("sprite[%d]    angle: |%f|\n",c, a->sprite[c].angle);
		printf("sprite[%d]  stature: |%f|\n",c, a->sprite[c].stature);
		printf("sprite[%d]     init: |%d|\n",c, a->sprite[c].init);
		printf("sprite[%d]      end: |%d|\n",c, a->sprite[c].end);
		printf("sprite[%d]  1st_ray: |%d|\n",c, a->sprite[c].first_ray);
		printf("sprite[%d]  lst_ray: |%d|\n\n",c, a->sprite[c].last_ray);*/
//		printf("yray: %d - xray: %d\n", (int)a->rayc.yray, (int)a->rayc.xray);
//		printf("xpos: %d - ypos: %d\n\n", a->sprite[a->fconf.map.nbr_sprite].xpos, a->sprite[a->fconf.map.nbr_sprite].ypos);
		c++;
	}
	printf("%d\n\n", i);
	i++;
}

void	print_addr(t_cub3d *a)
{
	int c = 0;

	while (a->mlibx.xpmwall[a->rayc.wall].addr && c < 100)
	{
	//	printf("dst: %s\n", (char *)a->mlibx.xpmwall[a->rayc.wall].addr);
		a->mlibx.xpmwall[a->rayc.wall].addr++;
		c++;
	}
	c = 4;
	printf("addr: %p\n", a->mlibx.xpmwall[c].addr);
	printf("bpp: %d\n", a->mlibx.xpmwall[c].bits_per_pixel);
	printf("line_len: %d\n", a->mlibx.xpmwall[c].line_length);
	printf("endian: %d\n", a->mlibx.xpmwall[c].endian);
	printf("img: %p\n", a->mlibx.xpmwall[c].img);
	printf("heigth: %d\n", a->mlibx.xpmwall[c].height);
	printf("width: %d\n", a->mlibx.xpmwall[c].width);
	printf("path: %s\n\n", a->mlibx.xpmwall[c].relative_path);
}

void	print_color(t_cub3d *a)
{
	int my_color;
	
	my_color = a->mlibx.xpmwall[a->rayc.wall].height * a->rayc.xtexture + a->rayc.ytexture;
	printf("img_heigth : %d\n", a->mlibx.xpmwall[a->rayc.wall].height);
	printf("xtexture: %d\n", a->rayc.xtexture);
	printf("ytexture: %d\n", a->rayc.ytexture);
	printf("my_color: %d\n", my_color);
	printf("color: %c\n\n", a->mlibx.xpmwall[a->rayc.wall].addr[my_color]);
}

void	print_wall(t_cub3d *a)
{
	printf("stature : %f\n", a->rayc.staturewall);
	printf("initwall: %d\n", a->rayc.initwall);
	printf("endwall : %d\n", a->rayc.endwall);
}

void	print_direction(t_cub3d *a)
{
/*	printf("quadrant: %d\n", a->rayc.quadrant);
	printf("xhit: %d\n", a->rayc.xhit);
	printf("yhit: %d\n", a->rayc.yhit);
	printf("xstep: %f - ystep: %f\n", a->rayc.xstep, a->rayc.ystep);
	printf("xwallhit: %f\n", a->rayc.xwallhit);
*/	printf("xtexture: %d\n", a->rayc.xtexture);
	printf("ytexture: %d\n\n", a->rayc.ytexture);
//	printf("ytexturefloat: %f - \n\n", a->rayc.ytexturefloat);
//	printf("steptexture: %f\n", a->rayc.ysteptexture);
}

void	print_divide(double x, int y)
{
	int f = (x * y) /1;
	printf("%d", f);
	exit (0);
}
void	print_struct(t_cub3d *a)
{

	printf("xrendersize: %d\n", a->fconf.xrendersize);
	printf("yrendersize: %d\n", a->fconf.yrendersize);
	printf("angulo FOV: |%f|\n", a->rayc.fov);
	printf("color ceil: |%x|\n", a->fconf.ceilcolor);
	printf("color floor: |%x|\n\n", a->fconf.floorcolor);
}

void	print_textures(t_cub3d *a)
{
	printf("north: %s - width %d - heigth %d\n", a->fconf.wall_texture[0], a->mlibx.xpmwall[0].width, a->mlibx.xpmwall[0].height);
	printf("south: %s - width %d - heigth %d\n", a->fconf.wall_texture[1], a->mlibx.xpmwall[1].width, a->mlibx.xpmwall[1].height);
	printf("west: %s - width %d - heigth %d\n", a->fconf.wall_texture[2], a->mlibx.xpmwall[2].width, a->mlibx.xpmwall[2].height);
	printf("east: %s - width %d - heigth %d\n\n", a->fconf.wall_texture[3], a->mlibx.xpmwall[3].width, a->mlibx.xpmwall[3].height);
	int c = 0;
	while (c <= 3)
	{
		printf("%p\n", a->mlibx.xpmwall[c].addr);
		printf("%d\n", a->mlibx.xpmwall[c].bits_per_pixel);
		printf("%d\n", a->mlibx.xpmwall[c].line_length);
		printf("%d\n", a->mlibx.xpmwall[c].endian);
		printf("%p\n", a->mlibx.xpmwall[c].img);
		printf("heigth: %d\n", a->mlibx.xpmwall[c].height);
		printf("width: %d\n", a->mlibx.xpmwall[c].width);
		printf("%s\n\n", a->mlibx.xpmwall[c].relative_path);
		c++;
	}
}

void	print_texture(t_cub3d *a)
{
	int c;
	
	c = a->rayc.wall;
	printf("%p\n", a->mlibx.xpmwall[c].addr);
	printf("%d\n", a->mlibx.xpmwall[c].bits_per_pixel);
	printf("%d\n", a->mlibx.xpmwall[c].line_length);
	printf("%d\n", a->mlibx.xpmwall[c].endian);
	printf("%p\n", a->mlibx.xpmwall[c].img);
	printf("heigth: %d\n", a->mlibx.xpmwall[c].height);
	printf("width: %d\n", a->mlibx.xpmwall[c].width);
	printf("%s\n\n", a->mlibx.xpmwall[c].relative_path);
}

void	print_fconfig(t_cub3d *a)
{
	int	i;

	i = 0;
	printf("row: %d\n", a->fconf.map.row);
	printf("colum: %zu\n", a->fconf.map.col);
	while (i <= a->fconf.map.row)
	{
		printf("linea %d: %s\n", i, a->fconf.map.maze[i]);
		i++;
	}
	i = 0;
	while (i <= 7 && a->fconf.wall_texture[i])
	{
		printf("TEXTURE[%d]:  |%s|\n", i, a->fconf.wall_texture[i]);
		i++;
	}
	printf("Last line with params: %d\n", a->fconf.final_line_params);
	printf("First line of map: %d\n", a->fconf.map.first_line);
	printf("final row: %d\n", a->fconf.map.row);
	printf("nº players: %d\n", a->fconf.map.num_players);
	i = 5;
	printf("Red[%d]: |%d|, Green[%d]: |%d| Blue[%d]: |%d|\n", i, a->fconf.red[i], i, a->fconf.green[i], i, a->fconf.blue[i]);
	i = 6;
	printf("Red[%d]: |%d|, Green[%d]: |%d| Blue[%d]: |%d|\n", i, a->fconf.red[i], i, a->fconf.green[i], i, a->fconf.blue[i]);
	printf("resX: %d\n", a->fconf.xrendersize);
	printf("resY: %d\n", a->fconf.yrendersize);
	printf("\n********** FIN IMPRESION ***********\n\n\n\n\n\n");
}

