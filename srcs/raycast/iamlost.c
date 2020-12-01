/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamlost.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 08:35:05 by ssacrist          #+#    #+#             */
/*   Updated: 2020/12/01 11:53:15 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_raycast(t_cub3d *a)
{
	a->rayc.ray = 0;
	while (a->rayc.ray < a->fconf.xrendersize)
	{
		//calculate ray position and direction
		a->rayc.xcamera = 2 * a->rayc.ray / (double)a->fconf.xrendersize - 1;//x-coordinate in camera space
		a->rayc.xraydir = a->rayc.xdir + a->rayc.xplane * a->rayc.xcamera;
		a->rayc.yraydir = a->rayc.ydir + a->rayc.yplane * a->rayc.xcamera;
		
		//which box of the map we're in
		a->rayc.xmap = (int)a->rayc.xpos;
		a->rayc.ymap = (int)a->rayc.ypos;
		
		//length of ray from current position to next x or y-side
		// a->rayc.xsidedist;
		// a->rayc.ysidedist;
		
		//length of ray from one x or y-side to next x or y-side
		a->rayc.xdeltadist = fabs(1 / a->rayc.xraydir);
		a->rayc.ydeltadist = fabs(1 / a->rayc.yraydir);
	
		//what direction to step in x or y-direction (either +1 or -1)
		// a->rayc.xstep;
		// a->rayc.ystep;
	
		a->rayc.hit = 0;
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
		while (a->rayc.hit != 1)
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
			if (a->fconf.map.maze[a->rayc.ymap][a->rayc.xmap] == '1')
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
		switch (a->fconf.map.maze[a->rayc.ymap][a->rayc.xmap])
		{
			case '1':		color = 0x00FF0000;	break;//red
			case '2':		color = 0x0000FF00;	break;//green
			case 3:		color = 0x000000FF;	break;//blue
			case 4:		color = 0x00FFFFFF;	break;//white
			default:	color = 0x00FFFF00;	break;//yellow
		}
		
		//give x and y sides different brightness
//		if (a->rayc.side == 1)
//			color = color / 2;
	
		//draw the pixels of the stripe as a vertical line
//		verLine(x, a->rayc.drawstart, a->rayc.drawend, color);
//		mlx_pixel_put(a->mlibx.mlx, a->mlibx.win, a->rayc.ray, a->rayc.drawend, color);
		print_struct(a);
		a->rayc.ray++;
	}

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
	a->rayc.rotspeed = a->rayc.frametime * 3.0;//the constant value is in squares/second
*/		
	return (0);
}
