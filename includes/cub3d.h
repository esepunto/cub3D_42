/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <ssacrist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 09:42:55 by ssacrist          #+#    #+#             */
/*   Updated: 2020/11/06 23:58:43 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>

typedef struct	s_raycast
{
	double	xpos;
	double	ypos;
	double	xdir;
	double	ydir;
	double	xplane;
	double	yplane;
	double	time;
	double	oldtime;
	double	xcamera;
	double	xraydir;
	double	yraydir;
	double	xmap;
	double	ymap;
	double	xsidedist;
	double	ysidedist;
	double	xdeltadist;
	double	ydeltadist;
	double	perpwalldist;
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
}				t_rayc;

typedef struct	s_map
{
	char		**map;
	size_t		col;
	int			row;
}				t_map;

typedef struct	s_readconfig
{
	char	*res;
	int		xrendersize;
	int		yrendersize;
	char	*wallno;
	char	*wallno_texture;
	char	*wallso;
	char	*wallso_texture;
	char	*wallea;
	char	*wallea_texture;
	char	*wallwe;
	char	*wallwe_texture;
	char	*sprite;
	char	*sprite_texture;
	char	*ceil;
	char	*flr;
	int		ceilclr;
	int		flrclr;
	int		init_id[8];
	t_map	map;
}				t_config;

typedef struct	s_cub3d
{
//	t_config	conf;
//	t_rayc		raycast;
	t_config	fconf;
//	t_map		map;
}				t_cub3d;

void	calc_fconfig(char *conf_file, t_cub3d *a);
void	save_fconfig(char *conf_file, t_cub3d *a);
void	read_fconfig(char *conf_file, t_cub3d *a);
void	print_fconfig(t_cub3d *a);
void	init_struct(t_cub3d *a);
int		main(int argc, char **argv);
int		msg_err(char *error);
void	find_walls(t_cub3d *a);
char	*look4_id(char *id, t_cub3d *a, int c);
char	*look4_id_2(const char *id, t_cub3d *a);
int		del_sp(int i, int j, t_cub3d *a);
void	errors_mgmt(char *id, t_cub3d *a, int c);
char	*look4_texture(char *str, char *id);
int		ft_isblank(int c);

#endif
