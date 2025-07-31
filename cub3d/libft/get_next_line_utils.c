/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:04:24 by evmouka           #+#    #+#             */
/*   Updated: 2025/07/22 11:07:23 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**get_content_array(void)
{
	static char	*content[1024] = {NULL};

	return (content);
}

void	gnl_cleanup_all(void)
{
	char		**content;
	int			i;

	content = get_content_array();
	i = 0;
	while (i < 1024)
	{
		if (content[i])
		{
			free(content[i]);
			content[i] = NULL;
		}
		i++;
	}
}
