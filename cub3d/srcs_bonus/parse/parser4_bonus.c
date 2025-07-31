/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:08:54 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/23 21:51:48 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

int	check_commas(const char *trimmed_line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (trimmed_line[i])
	{
		if (trimmed_line[i] == ',')
			commas += 1;
		i++;
	}
	i = 0;
	if (commas > 2)
		return (0);
	return (1);
}

int	handle_rgb_string(char **rgb_values, t_cub3d *cub3d)
{
	int		r;
	int		g;
	int		b;

	if (!check_rgb(rgb_values[0]) || !check_rgb(rgb_values[1])
		|| !check_rgb(rgb_values[2]))
	{
		free_string_array(rgb_values);
		return (print_and_return_error("Invalid RGB.", 0, cub3d), 0);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		free_string_array(rgb_values);
		return (print_and_return_error("RGB values must be between 0 and 255",
				0, cub3d), 0);
	}
	free_string_array(rgb_values);
	return ((r << 16) | (g << 8) | b);
}

int	parse_rgb_string(const char *trimmed_line, t_cub3d *cub3d)
{
	char	**rgb_values;

	if (!check_digits(trimmed_line + 2))
		return (print_and_return_error("Not valid values for colours",
				0, cub3d), 0);
	if (!check_commas(trimmed_line))
		return (print_and_return_error("invalid colour format",
				0, cub3d), 0);
	rgb_values = ft_split(trimmed_line + 2, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1]
		|| !rgb_values[2] || rgb_values[3])
	{
		if (rgb_values)
			free_string_array(rgb_values);
		return (print_and_return_error("Invalid RGB line format", 0, cub3d), 0);
	}
	return (handle_rgb_string(rgb_values, cub3d));
}

int	parse_colours(const char *trimmed_line, t_cub3d *cub3d)
{
	if (!cub3d || !trimmed_line)
		print_and_exit("Cub3D structure or line is NULL.", cub3d);
	if (cub3d->is_colours_set)
		return (print_and_return_error("Colours already set.", 0, cub3d), 0);
	if (ft_strncmp(trimmed_line, "C ", 2) == 0)
	{
		if (cub3d->colours.ceiling_colour != -1)
			return (print_and_return_error("Ceiling colour already set.",
					0, cub3d), 0);
		else
			cub3d->colours.ceiling_colour
				= parse_rgb_string(trimmed_line, cub3d);
	}
	else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
	{
		if (cub3d->colours.floor_colour != -1)
			return (print_and_return_error("Floor colour already set.",
					0, cub3d), 0);
		cub3d->colours.floor_colour = parse_rgb_string(trimmed_line, cub3d);
	}
	if (cub3d->colours.ceiling_colour != -1
		&& cub3d->colours.floor_colour != -1)
		cub3d->is_colours_set = true;
	return (1);
}
