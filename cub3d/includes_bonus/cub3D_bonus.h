/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:49:25 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/24 13:57:05 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# include "cub3d_struct_bonus.h"
# include "keycodes_bonus.h"
# include "textures_bonus.h"
# include "minimap_bonus.h"
# include "doors_bonus.h"

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>

# define PLANE 0.66
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03
# define COLLISION_BUFFER 0.5

# define MAX_MAP_WIDTH 100
# define MAX_MAP_HEIGHT 100

# define G "\33[032m"
# define R "\33[0;31m"
# define RESET "\33[0m"

# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 600
# define UNSET_FLAG	-1

/* parsing functions */

int		is_texture_line(const char *line);
int		is_colour_line(const char *line);
int		is_map_line(const char *line);
void	handle_map_start(t_cub3d *cub3d, char *line);
void	parse_line(char *line, t_cub3d *cub3d);
int		parse_scene_description_file(const char *filename, t_cub3d *cub3d);
char	*parse_texture_string(char *trimmed_line, t_cub3d *cub3d);
int		parse_textures(char *trimmed_line, t_cub3d *cub3d);
void	parse_textures_helper(char *trimmed_line, t_cub3d *cub3d);
int		parse_rgb_string(const char *trimmed_line, t_cub3d *cub3d);
int		handle_rgb_string(char **rgb_values, t_cub3d *cub3d);
int		parse_colours(const char *trimmed_line, t_cub3d *cub3d);
int		parse_map(const char *trimmed_line, t_cub3d *cub3d);
int		find_and_store_player_position(t_cub3d *cub3d,
			const char *trimmed_line);
int		player_direction_to_vector(t_cub3d *cub3d);
int		finalise_parsing(t_cub3d *cub3d);
int		validate_map(t_cub3d *cub3d);
int		floodfill(t_cub3d *cub3d, int x, int y);
int		is_walkable(char c);
int		validate_texture_file(char *texture_path, t_cub3d *cub3d);
void	check_all_textures_loaded(t_cub3d *cub3d);
void	east_west(t_cub3d *cub3d);
void	north_south(t_cub3d *cub3d);
/* utility functions */
int		validate_filename(const char *filename);
int		print_and_return(const char *message, int exit_code);
int		print_and_return_error(const char *message, int exit_code,
			t_cub3d *cub3d);
int		print_and_exit(const char *message, t_cub3d *cub3d);
void	free_texture(char **texture);
void	free_string_array(char **array);
void	free_cub3d_data(t_cub3d *cub3d);
void	free_line_and_exit(char *cleaned_line, t_cub3d *cub3d);
int		clean_exit(t_cub3d *cub3d);

void	load_textures_to_graphics(t_cub3d *cub3d);
int		check_digits(const char *trimmed_line);
int		check_rgb(char *rgb);
double	get_time_seconds(void);
/* init game*/
void	init_cub3d(t_cub3d *cub3d);
void	initialise_map_grid(t_cub3d *cub3d, int line_length);
int		graphics_init(t_cub3d *cub3d);

/* start game*/
int		start_game(t_cub3d *cub3d);
int		render_new_frame(t_cub3d *cub3d);
void	put_pixel_to_frame(t_cub3d *cub3d, int x, int y, int colour);
int		get_colour_from_texture(t_txtr txtr, t_vec2i txtr_pos);
int		darken_colour(int color, double distance);
void	draw_background_with_txtr(t_cub3d *cub3d);
void	draw_background_with_colour(t_cub3d *cub3d);

/*raycasting*/
void	raycasting(t_cub3d *cub3d);
void	calculate_wall_dist_with_doors(t_cub3d *cub3d, t_ray *ray);
void	draw_wall_line_with_doors(t_cub3d *cub3d, t_ray *ray, t_vec2i pixel);
t_txtr	choose_texture_for_line(t_cub3d *cub3d, t_ray *ray);

/*input*/
int		key_press(int keycode, t_cub3d *cub3d);
int		key_release(int keycode, t_cub3d *cub3d);
void	handle_input(t_cub3d *cub3d, t_player *pl);
void	move_forward(t_cub3d *cub3d, t_player *pl);
void	move_backward(t_cub3d *cub3d, t_player *pl);
void	strafe_left(t_cub3d *cub3d, t_player *pl);
void	strafe_right(t_cub3d *cub3d, t_player *pl);
void	rotate_to_left(t_player *pl);
void	rotate_to_right(t_player *pl);
int		mouse_move(int x, int y, void *param);
int		mouse_press(int keycode, int x, int y, void *param);

/*end of game*/
void	destroy_images(t_cub3d *cub3d);
void	free_all_alloc_memory(t_cub3d *cub3d);
void	free_txtr_paths(t_cub3d *cub3d);
int		game_end(t_cub3d *cub3d);
int		game_error(char *err_msg, t_cub3d *cub3d);

int		is_empty_line(const char *trimmed_line);

#endif