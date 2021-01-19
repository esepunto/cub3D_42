/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:14:38 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/19 11:41:40 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/*
** File config functions
*/

void		open_fconfig(char *conf_file, t_cub3d *a);
void		manage_params(t_cub3d *a);
void		review_params(t_cub3d *a);
void		check_rgb(int c, t_cub3d *a);
void		isdigit_str(char *nbr);
int			ceilfloorcolor(int c, t_cub3d *a);
void		extract_rgb(int c, t_cub3d *a);
void		manage_map(t_cub3d *a);
void		maze_algorithm(t_cub3d *a);

/*
** Window functions
*/

void		init_window(t_cub3d *a);
int			close_window(t_cub3d *a);
void		save_textures(t_cub3d *a);
void		pointillism(t_cub3d *a);
void		brushstroke(int x, int y, t_cub3d *a, int color);
void		paintsprites(t_cub3d *a);

/*
** Raycast functions
*/

void		throw_rays(t_cub3d *a);
void		calc_texturing(t_cub3d *a);
int			caress_key(t_cub3d *a);
void		found_sprite(t_cub3d *a);
void		clean_sprites(t_cub3d *a);
void		calc_init_ray(t_cub3d *a, int c);

/*
** Screenshot functions
*/

void		take_photo(t_cub3d *a);

/*
** Other functions
*/

int			msg_err(char *error);

/*
** Bonus functions
*/

void		print_lifepoints(t_cub3d *a);
//int			dark_color(t_cub3d *a);

#endif
