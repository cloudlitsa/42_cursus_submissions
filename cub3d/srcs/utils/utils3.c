/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:35:13 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/21 19:35:02 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_digits(const char *trimmed_line)
{
	int	i;

	i = 0;
	while (trimmed_line[i])
	{
		if (!ft_isdigit(trimmed_line[i]) && trimmed_line[i] != ' '
			&& trimmed_line[i] != ',' && trimmed_line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_rgb(char *rgb)
{
	int	i;
	int	digit_flag;

	i = 0;
	digit_flag = 0;
	while (rgb[i] && (rgb[i] == '\t' || rgb[i] == ' '))
		i++;
	if (!rgb[i] || !ft_isdigit(rgb[i]))
		return (0);
	while (rgb[i] && ft_isdigit(rgb[i]))
	{
		digit_flag = 1;
		i++;
	}
	if (!digit_flag)
		return (0);
	while (rgb[i] && (rgb[i] == '\t' || rgb[i] == ' '))
		i++;
	return (digit_flag && rgb[i] == '\0');
}

int	validate_filename(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4))
	{
		printf("Error\n");
		printf(R "Invalid file extension.");
		printf(" Expected '.cub' but got '%s'\n"RESET, filename);
		return (0);
	}
	return (1);
}
