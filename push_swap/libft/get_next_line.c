/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:33:55 by joolim            #+#    #+#             */
/*   Updated: 2023/10/29 16:44:52 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_file(int fd, char *buffer)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (ft_strchr_gnl(buffer, '\n') == NULL && bytes_read != 0)
	{
		tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (NULL);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			if (buffer)
				free(buffer);
			free(tmp);
			return (NULL);
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, tmp);
		free(tmp);
	}
	return (buffer);
}

static char	*get_line(char *buffer)
{
	size_t	len;
	size_t	i;
	char	*line;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	if (ft_strchr_gnl(buffer, '\n') != NULL)
		len = (size_t)(ft_strchr_gnl(buffer, '\n') - buffer) + 1;
	else
		len = ft_strlen_gnl(buffer);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*line;
	char	*newline;
	size_t	len;
	size_t	i;

	i = 0;
	newline = ft_strchr_gnl(buffer, '\n');
	if (!newline)
	{
		free(buffer);
		return (NULL);
	}
	newline += 1;
	len = ft_strlen_gnl(newline);
	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	while (i < len && *newline != '\0')
		line[i++] = *(newline++);
	line[i] = '\0';
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}
