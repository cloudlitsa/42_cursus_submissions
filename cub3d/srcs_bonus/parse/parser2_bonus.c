/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:21:01 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/24 13:48:17 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

void	help_parse_line(char *trimmed_line, char *line, t_cub3d *cub3d)
{
	if (!cub3d->map_started && is_texture_line(trimmed_line))
		parse_textures(trimmed_line, cub3d);
	else if (!cub3d->map_started && is_colour_line(trimmed_line))
		parse_colours(trimmed_line, cub3d);
	else if (is_empty_line(trimmed_line))
		return ;
	else if (is_map_line(trimmed_line))
		handle_map_start(cub3d, line);
	else
		print_and_return_error("Invalid line in file", 0, cub3d);
}

static void	r_cl(char *trimmed_line, t_cub3d *cub3d, char *msg)
{
	print_and_return_error (msg, 0, cub3d);
	free(trimmed_line);
}

void	parse_line(char *line, t_cub3d *cub3d)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r\v\f");
	if (!cub3d || !trimmed_line)
	{
		free(trimmed_line);
		print_and_exit("cub3D structure or line is NULL.", cub3d);
	}
	if (ft_strlen(trimmed_line) == 0 && !cub3d->map_started)
		return (free(trimmed_line));
	if (cub3d->map_started && cub3d->empty_line && is_map_line(trimmed_line))
		return (r_cl(trimmed_line, cub3d, "Empty line in the map"));
	if (cub3d->map_started && is_empty_line(trimmed_line))
	{
		cub3d->empty_line = true;
		return (free(trimmed_line));
	}
	if (cub3d->map_started && !is_map_line(trimmed_line) && !cub3d->empty_line)
		return (r_cl(trimmed_line, cub3d, "Invalid map line"));
	help_parse_line(trimmed_line, line, cub3d);
	free(trimmed_line);
}

char	*parse_texture_string(char *trimmed_line, t_cub3d *cub3d)
{
	char	**texture_string;
	char	*texture_path;

	texture_string = ft_split(trimmed_line, ' ');
	if (!texture_string)
		print_and_exit("Memory allocation failed for texture string", cub3d);
	if (!texture_string[0] || !texture_string[1] || texture_string[2])
	{
		free_string_array(texture_string);
		print_and_return_error("Invalid texture line format", 0, cub3d);
		return (NULL);
	}
	texture_path = ft_strdup(texture_string[1]);
	free_string_array(texture_string);
	if (!texture_path)
		print_and_exit("Memory allocation failed for texture path", cub3d);
	return (texture_path);
}

int	parse_textures(char *trimmed_line, t_cub3d *cub3d)
{
	char	*texture_path;

	if (!cub3d || !trimmed_line)
		print_and_exit("cub3D structure or line is NULL.", cub3d);
	check_all_textures_loaded(cub3d);
	if (cub3d->is_textures_loaded)
		return (print_and_return_error("Mandatory textures already set.",
				0, cub3d), 0);
	texture_path = parse_texture_string(trimmed_line, cub3d);
	if (!validate_texture_file(texture_path, cub3d))
	{
		free(texture_path);
		return (print_and_return_error("Invalid texture file path.",
				0, cub3d), 0);
	}
	free(texture_path);
	parse_textures_helper(trimmed_line, cub3d);
	return (1);
}
