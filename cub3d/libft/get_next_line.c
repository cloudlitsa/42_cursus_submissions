/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmouka <evmouka@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:43:59 by evmouka           #+#    #+#             */
/*   Updated: 2025/06/05 11:41:31 by evmouka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_file(int fd)
{
	ssize_t	bytes_read;
	char	buffer[BUFFER_SIZE + 1];

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (ft_strdup(buffer));
}

static char	*concat_strings(char *s1, char *s2)
{
	char	*result;

	result = NULL;
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static char	*read_and_concat(int fd, char **content)
{
	char	*read_result;

	read_result = read_file(fd);
	if (!read_result)
		return (NULL);
	*content = concat_strings(*content, read_result);
	free(read_result);
	return (*content);
}

static char	*extract_line(char **content)
{
	char	*line;
	ssize_t	i;
	char	*new_content;

	if (*content == NULL || (*content)[0] == '\0')
		return (NULL);
	i = 0;
	while ((*content)[i] != '\n' && (*content)[i] != '\0')
		i++;
	if ((*content)[i] == '\n')
		i++;
	line = ft_substr(*content, 0, i);
	if ((*content)[i] == '\0')
	{
		free(*content);
		*content = NULL;
	}
	else
	{
		new_content = ft_substr(*content, i, ft_strlen(*content));
		free(*content);
		*content = new_content;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	**content;

	content = get_content_array();
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (content[fd] && ft_strchr(content[fd], '\n'))
		return (extract_line(&content[fd]));
	if (!(read_and_concat(fd, &content[fd])))
	{
		if (content[fd])
			return (extract_line(&content[fd]));
		return (NULL);
	}
	while (content[fd] && !ft_strchr(content[fd], '\n'))
	{
		if (!read_and_concat(fd, &content[fd]))
			break ;
	}
	if (!content[fd] || content[fd][0] == '\0')
		return (NULL);
	return (extract_line(&content[fd]));
}
