/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:22:02 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/24 13:47:06 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

int	is_texture_line(const char *trimmed_line)
{
	int		result;

	if (!trimmed_line || ft_strlen(trimmed_line) < 3)
		return (0);
	result = ft_strncmp(trimmed_line, "NO ", 3) == 0
		|| ft_strncmp(trimmed_line, "SO ", 3) == 0
		|| ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0;
	return (result);
}

int	is_colour_line(const char *trimmed_line)
{
	int		result;

	if (!trimmed_line || ft_strlen(trimmed_line) < 2)
		return (0);
	if (ft_strlen(trimmed_line) > 2 && trimmed_line[1] != ' ')
		return (0);
	result = ft_strncmp(trimmed_line, "C ", 2) == 0
		|| ft_strncmp(trimmed_line, "F ", 2) == 0;
	return (result);
}

int	is_empty_line(const char *trimmed_line)
{
	if (!trimmed_line || ft_strlen(trimmed_line) == 0
		|| trimmed_line[0] == '\n')
		return (1);
	else
		return (0);
}

int	is_map_line(const char *trimmed_line)
{
	int		i;

	if (!trimmed_line || ft_strlen(trimmed_line) == 0
		|| trimmed_line[0] == '\n')
		return (0);
	i = 0;
	while (trimmed_line[i])
	{
		if (trimmed_line[i] != '0' && trimmed_line[i] != '1'
			&& trimmed_line[i] != 'N' && trimmed_line[i] != 'S'
			&& trimmed_line[i] != 'E' && trimmed_line[i] != 'W'
			&& trimmed_line[i] != 'D' && trimmed_line[i] != ' ')
			return (0);
		if (trimmed_line[i] == '0' && trimmed_line[i + 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int	parse_scene_description_file(const char *filename, t_cub3d *cub3d)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_and_exit("Error opening file", cub3d);
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		parse_line(line, cub3d);
		if (line)
			free(line);
		line = NULL;
		if (!cub3d->error)
			line = get_next_line(fd);
	}
	close(fd);
	if (line_count == 0)
		print_and_exit("No lines read from the file.", cub3d);
	if (!finalise_parsing(cub3d))
		clean_exit(cub3d);
	return (1);
}
