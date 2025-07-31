/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 22:15:08 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/23 19:51:31 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3D_bonus.h"

int	print_and_return(const char *message, int exit_code)
{
	printf("Error\n");
	printf(R "%s\n" RESET, message);
	return (exit_code);
}

int	print_and_return_error(const char *message, int exit_code, t_cub3d *cub3d)
{
	cub3d->error = true;
	printf("Error\n");
	printf(R "%s\n" RESET, message);
	return (exit_code);
}

int	print_and_exit(const char *message, t_cub3d *cub3d)
{
	cub3d->error = true;
	get_next_line(-1);
	printf("Error\n");
	printf(R "%s\n" RESET, message);
	if (cub3d)
		free_cub3d_data(cub3d);
	exit(EXIT_FAILURE);
}

int	clean_exit(t_cub3d *cub3d)
{
	cub3d->error = true;
	get_next_line(-1);
	if (cub3d)
		free_cub3d_data(cub3d);
	exit(EXIT_FAILURE);
}
