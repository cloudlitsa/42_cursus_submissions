/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:43:40 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/21 15:22:59 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	assign_no_so_texture(char *trimmed_line, t_cub3d *cub3d)
{
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
	{
		if (cub3d->textures.north)
			print_and_return_error("North texture already set", 0, cub3d);
		else
			cub3d->textures.north = parse_texture_string(trimmed_line, cub3d);
	}
	if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
	{
		if (cub3d->textures.south)
			print_and_return_error("South texture already set", 0, cub3d);
		else
			cub3d->textures.south = parse_texture_string(trimmed_line, cub3d);
	}
}

static void	assign_ea_we_texture(char *trimmed_line, t_cub3d *cub3d)
{
	if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
	{
		if (cub3d->textures.west)
			print_and_return_error("West texture already set", 0, cub3d);
		else
			cub3d->textures.west = parse_texture_string(trimmed_line, cub3d);
	}
	if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
	{
		if (cub3d->textures.east)
			print_and_return_error("East texture already set", 0, cub3d);
		else
			cub3d->textures.east = parse_texture_string(trimmed_line, cub3d);
	}
}

void	parse_textures_helper(char *trimmed_line,	t_cub3d *cub3d)
{
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0
		|| ft_strncmp(trimmed_line, "SO ", 3) == 0)
		assign_no_so_texture(trimmed_line, cub3d);
	else if (ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
		assign_ea_we_texture(trimmed_line, cub3d);
	else
		print_and_return_error("Invalid identifier or texture loaded",
			0, cub3d);
}

void	check_all_textures_loaded(t_cub3d *cub3d)
{
	if (cub3d->textures.north && cub3d->textures.south
		&& cub3d->textures.west && cub3d->textures.east)
	{
		cub3d->is_textures_loaded = true;
	}
}

int	validate_texture_file(char *texture_path, t_cub3d *cub3d)
{
	int	fd;

	if (!texture_path || ft_strlen(texture_path) == 0)
		return (cub3d->error = true, 0);
	if (ft_strncmp(texture_path + (ft_strlen(texture_path) - 4), ".xpm", 4))
		return (cub3d->error = true, 0);
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
