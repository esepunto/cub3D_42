/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssacrist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:14:38 by ssacrist          #+#    #+#             */
/*   Updated: 2021/01/13 02:47:38 by ssacrist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

int		main(int argc, char **argv);
void	open_fconfig(char *conf_file, t_cub3d *a);
void	manage_params(t_cub3d *a);
void	review_params(t_cub3d *a);
void	check_nbr(int c, t_cub3d *a);
void	isdigit_str(char *nbr);
void	extract_rgb(int c, t_cub3d *a);
void	manage_map(t_cub3d *a);
void	maze_algorithm(t_cub3d *a);
int		ceilfloorcolor(int c, t_cub3d *a);

void	save_textures(t_cub3d *a);

void	init_window(t_cub3d *a);
int		caress_key(int keycode, t_cub3d *a);
int		close_window(t_cub3d *a);

void	throw_rays(t_cub3d *a);
void	calc_texturing(t_cub3d *a);
void	pointillism(t_cub3d *a);
void	brushstroke(int x, int y, t_cub3d *a, int color);

void	found_sprite(t_cub3d *a);
void	allocate_sprites(t_cub3d *a);
void	save_sprites(t_cub3d *a);
void	clean_sprites(t_cub3d *a);
void	sort_sprites(t_cub3d *a);
void	calc_stature_sprite(t_cub3d *a, int point);
void	paintsprites(t_cub3d *a);

void	take_photo(t_cub3d *a);

int		msg_err(char *error);
void	delmem(t_cub3d *a);

void	print_fconfig(t_cub3d *a);
void	print_struct(t_cub3d *a);
void	print_textures(t_cub3d *a);
void	print_texture(t_cub3d *a);
void	print_divide(double x, int y);
void	print_direction(t_cub3d *a);
void	print_wall(t_cub3d *a);
void	print_color(t_cub3d *a);
void	print_addr(t_cub3d *a);
void	print_sprites(t_cub3d *a);

#endif
