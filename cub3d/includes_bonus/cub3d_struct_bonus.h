/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_struct_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:45:44 by mosokina          #+#    #+#             */
/*   Updated: 2025/07/24 13:45:40 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCT_BONUS_H
# define CUB3D_STRUCT_BONUS_H

# include <stdbool.h>

# define DOORS_MAX 5

typedef struct s_vec2i
{
	int		x;
	int		y;
}	t_vec2i;

typedef struct s_vec2d
{
	double		x;
	double		y;
}	t_vec2d;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*ceiling;
	char	*floor;
}	t_textures;

typedef struct s_colours
{
	int	floor_colour;
	int	ceiling_colour;
}	t_colours;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	player_orientation;
}	t_map;

typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	int		move_forward;
	int		move_backward;
	int		strafe_left;
	int		strafe_right;
	int		rotate_left;
	int		rotate_right;
	int		mouse_press;
}	t_player;

typedef enum e_hit_type
{
	NO_HIT,
	HIT_WALL,
	HIT_CLOSED_DOOR,
	HIT_ANIMATED_DOOR,
	PASS_THR_ANIMATED_DOOR,
}	t_hit_type;

typedef enum e_door_state
{
	CLOSED,
	OPENING,
	OPEN,
	CLOSING
}	t_door_state;

typedef struct s_door
{
	t_vec2i			map_pos;
	t_door_state	state;
	float			timer;
	bool			is_locked;
}	t_door;

typedef struct s_ray
{
	t_vec2d		dir;
	double		camera_x;
	t_vec2i		map;
	t_vec2d		delta_dist;
	t_vec2d		side_dist;
	t_vec2d		map_hit;
	t_vec2i		step;
	int			side;
	double		wall_dist;
	double		line_height;
	int			draw_start;
	int			draw_end;
	double		door_texx;
	double		door_hit_x;
	t_hit_type	hit_type;
}	t_ray;

typedef enum e_texture_type
{
	TX_NORTH,
	TX_SOUTH,
	TX_WEST,
	TX_EAST,
	TX_FLOOR,
	TX_CEILING,
	TX_DOOR,
	TXTRS_NBR
}	t_texture_type;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_txtr
{
	char	*txtr_path;
	t_img	img;
	int		width;
	int		height;
}	t_txtr;

typedef struct s_cub3d
{
	void		*mlx;
	void		*mlx_win;
	int			win_width;
	int			win_height;
	t_img		frame_buf;
	t_txtr		txtrs[TXTRS_NBR];
	t_player	player;
	t_ray		ray;
	t_textures	textures;
	t_colours	colours;
	t_map		map;
	bool		is_map_valid;
	bool		is_textures_loaded;
	bool		is_colours_set;
	bool		map_started;
	bool		error;
	t_door		doors[DOORS_MAX];
	int			door_count;
	double		last_frame_time;
	t_door		*animated_door;
	bool		draw_background_with_txtr;
	bool		empty_line;
}	t_cub3d;

typedef struct s_floor
{
	t_vec2d	dir;
	double	camera_x;
	double	floor_dist;
	t_vec2d	floor_pos;
}	t_floor;

#endif