/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamlost.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 08:35:05 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/26 10:09:16 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_raycast(t_cub3d *a)
{
	a->rayc.ray = 0;
	print_struct(a);
	while (a->rayc.ray < a->fconf.yrendersize)
	{
		
//		print_struct(a);
		//calculate ray position and direction
		a->rayc.xcamera = 2 * a->rayc.ray / (double)a->fconf.yrendersize - 1;//x-coordinate in camera space
		a->rayc.xraydir = a->rayc.xdir + a->rayc.xplane * a->rayc.xcamera;
		a->rayc.yraydir = a->rayc.ydir + a->rayc.yplane * a->rayc.ycamera;
		
		//which box of the map we're in
		a->rayc.xmap = (int)a->rayc.xpos;
		a->rayc.ymap = (int)a->rayc.ypos;
		
		//length of ray from current position to next x or y-side
		// a->rayc.xsidedist;
		// a->rayc.ysidedist;
		
		//length of ray from one x or y-side to next x or y-side
		a->rayc.xdeltadist = sqrt(1 + (a->rayc.yraydir * a->rayc.yraydir) / (a->rayc.xraydir * a->rayc.xraydir));
		a->rayc.ydeltadist = sqrt(1 + (a->rayc.xraydir * a->rayc.xraydir) / (a->rayc.yraydir * a->rayc.yraydir));
//		a->rayc.xdeltadist = fabs(1 / a->rayc.xraydir);
//		a->rayc.ydeltadist = fabs(1 / a->rayc.yraydir);
	
		//what direction to step in x or y-direction (either +1 or -1)
		// a->rayc.xstep;
		// a->rayc.ystep;
	
		a->rayc.hit = 0;//was there a wall hit?
//		a->rayc.side;//was a NS or a EW wall hit?
	
		//calculate step and initial sideDist
		if (a->rayc.xdir < 0)
		{
			a->rayc.xstep = -1;
			a->rayc.xsidedist = (a->rayc.xpos - a->rayc.xmap) * a->rayc.xdeltadist;
		}
		else
		{
			a->rayc.xstep = 1;
			a->rayc.xsidedist = (a->rayc.xmap + 1.0 - a->rayc.xpos) * a->rayc.xdeltadist;
		}
		if (a->rayc.ydir < 0)
		{
			a->rayc.ystep = -1;
			a->rayc.ysidedist = (a->rayc.ypos - a->rayc.ymap) * a->rayc.ydeltadist;
		}
		else
		{
			a->rayc.ystep = 1;
			a->rayc.ysidedist = (a->rayc.ymap + 1.0 - a->rayc.ypos) * a->rayc.ydeltadist;
		}
		
		//DDA algorithm
		while (a->rayc.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (a->rayc.xsidedist < a->rayc.ysidedist)
			{
				a->rayc.xsidedist += a->rayc.xdeltadist;
				a->rayc.xmap += a->rayc.xstep;
				a->rayc.side = 0;
			}
			else
			{
				a->rayc.ysidedist += a->rayc.ydeltadist;
				a->rayc.ymap += a->rayc.ystep;
				a->rayc.side = 1;
			}
			//Check if ray has hit a wall
			if (a->fconf.map.maze[a->rayc.xmap][a->rayc.ymap] > 0)
				a->rayc.hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (a->rayc.side == 0)
			a->rayc.perpwalldist = (a->rayc.xmap - a->rayc.xpos + (1 - a->rayc.xstep) / 2) / a->rayc.xraydir;
		else
			a->rayc.perpwalldist = (a->rayc.ymap - a->rayc.ypos + (1 - a->rayc.ystep) / 2) / a->rayc.yraydir;
	
		//Calculate height of line to draw on screen ( h = height in pixels of the screen)
		a->rayc.lineheight = (int)(a->fconf.xrendersize / a->rayc.perpwalldist);
		
		//calculate lowest and highest pixel to fill in current stripe
		a->rayc.drawstart = -a->rayc.lineheight / 2 + a->fconf.xrendersize / 2;
		if (a->rayc.drawstart < 0)
			a->rayc.drawstart = 0;
		a->rayc.drawend = a->rayc.lineheight / 2 + a->fconf.xrendersize / 2;
		if (a->rayc.drawend >= a->rayc.lineheight)
			a->rayc.drawend = a->rayc.lineheight - 1;
	
		//choose wall color
		long	color;
		switch (a->fconf.map.maze[a->rayc.xmap][a->rayc.ymap])
		{
			case 1:		color = 0x00FF0000;	break;//red
			case 2:		color = 0x0000FF00;	break;//green
			case 3:		color = 0x000000FF;	break;//blue
			case 4:		color = 0x00FFFFFF;	break;//white
			default:	color = 0x00FFFF00;	break;//yellow
		}
		
		//give x and y sides different brightness
		if (a->rayc.side == 1)
			color = color / 2;
	
		//draw the pixels of the stripe as a vertical line
//		verLine(x, a->rayc.drawstart, a->rayc.drawend, color);
//		mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, a->rayc.ray, a->rayc.drawend, color);

		a->rayc.ray++;
	}
//	print_struct(a);
	//exit(0);
/*	
	//timing for input and FPS counter
	a->rayc.oldtime = a->rayc.time;
	a->rayc.time = getTicks();
	a->rayc.frametime = (a->rayc.time - a->rayc.oldtime) / 1000.0;//frameTime is the time this frame has taken, in seconds
	print(1.0 / a->rayc.frametime);//FPS counter
	redraw();
	cls();
*/	
/*	//speed modifiers
	a->rayc.movespeed = a->rayc.frametime * 5.0;//the constant value is in squares/second
	a->rayc.rootspeed = a->rayc.frametime * 3.0;//the constant value is in squares/second
*/		
//	readkeys;
	mlx_hook(a->mlibx.win, 2, 1L << 17, caress_key, a);
	return (0);
}



/*
** VER ABAJO VERSIÓN COMPLETA DE LA FUNCIÓN
*/


/*
int	init_raycast(t_cub3d *a)
{
	a->rayc.ray = 0;
	
	while (a->rayc.ray < a->fconf.yrendersize)
	{
		
		//calculate ray position and direction
		a->rayc.xcamera = 2 * a->rayc.ray / (double)a->fconf.yrendersize - 1;//x-coordinate in camera space
//		a->rayc.xcamera = 2 * x / (double)w - 1;//x-coordinate in camera space
		a->rayc.xraydir = a->rayc.xdir + a->rayc.xplane * a->rayc.xcamera;
		a->rayc.yraydir = a->rayc.ydir + a->rayc.yplane * a->rayc.ycamera;
		
		//which box of the map we're in
		a->rayc.xmap = (int)a->rayc.xpos;
		a->rayc.ymap = (int)a->rayc.ypos;
		
		//length of ray from current position to next x or y-side
		// a->rayc.xsidedist;
		// a->rayc.ysidedist;
		
		//length of ray from one x or y-side to next x or y-side
		
		** deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		** deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		** But this can be simplified to:
		** deltaDistX = abs(|v| / rayDirX)
		
		a->rayc.xdeltadist = sqrt(1 + (a->rayc.yraydir * a->rayc.yraydir) / (a->rayc.xraydir * a->rayc.xraydir));
		a->rayc.ydeltadist = sqrt(1 + (a->rayc.xraydir * a->rayc.xraydir) / (a->rayc.yraydir * a->rayc.yraydir));
//		a->rayc.xdeltadist = fabs(1 / a->rayc.xraydir);
//		a->rayc.ydeltadist = fabs(1 / a->rayc.yraydir);
//		 Alternative code for deltaDist in case division through zero is not supported
//		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
//		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));
//		a->rayc.xdeltadist = (a->rayc.yraydir == 0) ? 0 : ((a->rayc.xraydir == 0) ? 1 : fabs(1 / a->rayc.xraydir));
//		a->rayc.ydeltadist = (a->rayc.xraydir == 0) ? 0 : ((a->rayc.yraydir == 0) ? 1 : fabs(1 / a->rayc.yraydir));

		
		** ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		** Alternative code for deltaDist in case division through zero is not supported
		** double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : abs(1 / rayDirX));
		** double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : abs(1 / rayDirY));
		
		// a->rayc.perpwalldist;
	
		//what direction to step in x or y-direction (either +1 or -1)
		// a->rayc.xstep;
		// a->rayc.ystep;
	
		a->rayc.hit = 0;//was there a wall hit?
//		a->rayc.side;//was a NS or a EW wall hit?
	
		//calculate step and initial sideDist
		if (a->rayc.xdir < 0)
		{
			a->rayc.xstep = -1;
			a->rayc.xsidedist = (a->rayc.xpos - a->rayc.xmap) * a->rayc.xdeltadist;
		}
		else
		{
			a->rayc.xstep = 1;
			a->rayc.xsidedist = (a->rayc.xmap + 1.0 - a->rayc.xpos) * a->rayc.xdeltadist;
		}
		if (a->rayc.ydir < 0)
		{
			a->rayc.ystep = -1;
			a->rayc.ysidedist = (a->rayc.ypos - a->rayc.ymap) * a->rayc.ydeltadist;
		}
		else
		{
			a->rayc.ystep = 1;
			a->rayc.ysidedist = (a->rayc.ymap + 1.0 - a->rayc.ypos) * a->rayc.ydeltadist;
		}
		
		//DDA algorithm
		while (a->rayc.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (a->rayc.xsidedist < a->rayc.ysidedist)
			{
				a->rayc.xsidedist += a->rayc.xdeltadist;
				a->rayc.xmap += a->rayc.xstep;
				a->rayc.side = 0;
			}
			else
			{
				a->rayc.ysidedist += a->rayc.ydeltadist;
				a->rayc.ymap += a->rayc.ystep;
				a->rayc.side = 1;
			}
			//Check if ray has hit a wall
			if (a->fconf.map.maze[a->rayc.xmap][a->rayc.ymap] > 0)
				a->rayc.hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (a->rayc.side == 0)
			a->rayc.perpwalldist = (a->rayc.xmap - a->rayc.xpos + (1 - a->rayc.xstep) / 2) / a->rayc.xraydir;
		else
			a->rayc.perpwalldist = (a->rayc.ymap - a->rayc.ypos + (1 - a->rayc.ystep) / 2) / a->rayc.yraydir;
	
		//Calculate height of line to draw on screen ( h = height in pixels of the screen)
		a->rayc.lineheight = (int)(a->fconf.xrendersize / a->rayc.perpwalldist);
		
		//calculate lowest and highest pixel to fill in current stripe
		a->rayc.drawstart = -a->rayc.lineheight / 2 + a->fconf.xrendersize / 2;
		if (a->rayc.drawstart < 0)
			a->rayc.drawstart = 0;
		a->rayc.drawend = a->rayc.lineheight / 2 + a->fconf.xrendersize / 2;
		if (a->rayc.drawend >= a->rayc.lineheight)
			a->rayc.drawend = a->rayc.lineheight - 1;
	
		//choose wall color
		long	color;
		switch (a->fconf.map.maze[a->rayc.xmap][a->rayc.ymap])
		{
		
			case 1:		color = RGB_Red;	break;//red
			case 2:		color = RGB_Green;	break;//green
			case 3:		color = RGB_Blue;	break;//blue
			case 4:		color = RGB_White;	break;//white
			default:	color = RGB_Yellow;	Break;//yellow
				
			case 1:		color = 0x00FF0000;	break;//red
			case 2:		color = 0x0000FF00;	break;//green
			case 3:		color = 0x000000FF;	break;//blue
			case 4:		color = 0x00FFFFFF;	break;//white
			default:	color = 0x00FFFF00;	break;//yellow
		}
		
		//give x and y sides different brightness
		if (a->rayc.side == 1)
			color = color / 2;
	
		//draw the pixels of the stripe as a vertical line
//		verLine(x, a->rayc.drawstart, a->rayc.drawend, color);
		mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, a->rayc.drawstart, a->rayc.drawend, color);
//		printf("color: %d\n", a->rayc.drawstart);
		
	}
	a->rayc.ray++;
	exit(0);
	
	//timing for input and FPS counter
	a->rayc.oldtime = a->rayc.time;
	a->rayc.time = getTicks();
	a->rayc.frametime = (a->rayc.time - a->rayc.oldtime) / 1000.0;//frameTime is the time this frame has taken, in seconds
	print(1.0 / a->rayc.frametime);//FPS counter
	redraw();
	cls();
	
	//speed modifiers
	a->rayc.movespeed = a->rayc.frametime * 5.0;//the constant value is in squares/second
	a->rayc.rootspeed = a->rayc.frametime * 3.0;//the constant value is in squares/second
		
	readkeys();
	//move forward if no wall in front of you
	if (keyDown(SDLK_UP))
	{
		if (a->fconf.map.maze[int(a->rayc.xpos + a->rayc.xdir * a->rayc.movespeed)][int(a->rayc.ypos)] == false)
			a->rayc.xpos += a->rayc.xdir * a->rayc.movespeed;
		if (a->fconf.map.maze[int(a->rayc.xpos)][int(a->rayc.ypos + a->rayc.ydir * a->rayc.movespeed)] == false)
			a->rayc.ypos += a->rayc.ydir * a->rayc.movespeed;
	}
	//move backwards if no wall behind you
	if (keyDown(SDLK_DOWN))
	{
		if(a->fconf.map.maze[int(a->rayc.xpos - a->rayc.xdir * a->rayc.movespeed)][int(a->rayc.ypos)] == false)
			a->rayc.xpos -= a->rayc.xdir * a->rayc.movespeed;
		if(a->fconf.map.maze[int(a->rayc.xpos)][int(a->rayc.ypos - dirY * a->rayc.movespeed)] == false)
			a->rayc.ypos -= a->rayc.ydir * a->rayc.movespeed;
	}
	//rotate to the right
	if (keyDown(SDLK_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		a->rayc.xolddir = a->rayc.xdir;
		a->rayc.xdir = a->rayc.xdir * cos(-a->rayc.rotspeed) - a->rayc.ydir * sin(-a->rayc.rotspeed);
		a->rayc.ydir = a->rayc.xolddir * sin(-a->rayc.rotspeed) + a->rayc.ydir * cos(-a->rayc.rotspeed);
		a->rayc.xoldplane = a->rayc.xplane;
		a->rayc.xplane = a->rayc.xplane * cos(-a->rayc.rotspeed) - a->rayc.yplane * sin(-a->rayc.rotspeed);
		a->rayc.yplane = a->rayc.xoldplane * sin(-a->rayc.rotspeed) + a->rayc.yplane * cos(-a->rayc.rotspeed);
	}
	//rotate to the left
	if (keyDown(SDLK_LEFT))
	{
		//both camera direction and camera plane must be rotated
		a->rayc.xolddir = a->rayc.xdir;
		a->rayc.xdir = a->rayc.xdir * cos(a->rayc.rotSpeed) - a->rayc.ydir * sin(a->rayc.rotSpeed);
		a->rayc.ydir = a->rayc.xolddir * sin(a->rayc.rotspeed) + a->rayc.ydir * cos(a->rayc.rotspeed);
		a->rayc.xoldplane = a->rayc.xplane;
		a->rayc.xplane = a->rayc.xplane * cos(a->rayc.rotspeed) - a->rayc.yplane * sin(a->rayc.rotspeed);
		a->rayc.yplane = a->rayc.xoldplane * sin(a->rayc.rotspeed) + a->rayc.yplane * cos(a->rayc.rotspeed);
	}

	}
	return (0);
}
*/
