/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:36:00 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/26 10:06:44 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void print_struct(t_cub3d *a)
{
	printf("key: %d\n", a->rayc.keycode);
	printf("xrendersize: %d\n", a->fconf.xrendersize);
	printf("yrendersize: %d\n", a->fconf.yrendersize);
	printf("ray: %d\n", a->rayc.ray);
	printf("xpos: %f - ", a->rayc.xpos);
	printf("ypos: %f\n", a->rayc.ypos);
	printf("xdir: %f - ", a->rayc.xdir);
	printf("ydir: %f\n", a->rayc.ydir);
	printf("xcamera: %f - ", a->rayc.xcamera);
	printf("ycamera: %f\n", a->rayc.ycamera);
	printf("xmap: %d - ", a->rayc.xmap);
	printf("ymap: %d\n", a->rayc.ymap);
	printf("xplane: %f - ", a->rayc.xplane);
	printf("yplane: %f\n", a->rayc.yplane);
	printf("xraydir: %f - ", a->rayc.xraydir);
	printf("yraydir: %f\n", a->rayc.yraydir);
	printf("xsidedist: %f - ", a->rayc.xsidedist);
	printf("ysidedist: %f\n", a->rayc.ysidedist);
	printf("xdeltadist: %f - ", a->rayc.xdeltadist);
	printf("ydeltadist: %f\n", a->rayc.ydeltadist);
	printf("perpwalldist: %f\n\n", a->rayc.perpwalldist);
}
/*
	char	plyr;
	double	time;
	double	oldtime;
	int		xstep;
	int		ystep;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	frametime;
	double	movespeed;
	double	rootspeed;
	double	xolddir;
	double	yolddir;
	double	xoldplane;
*/
