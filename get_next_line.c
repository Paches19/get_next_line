/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:42:50 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/26 16:37:59 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_buf(char **save_read, char *buf)
{
	int		i;
	int		j;
	char	*temp;

	temp = (char *) ft_calloc(ft_strlen(*save_read, 0) + ft_strlen(buf, 0) \
	+ 1, 1);
	i = 0;
	while (temp[i])
		++i;
	j = -1;
	while (buf[++j])
		temp[i++] = buf[j];
	free (*save_read);
	return (temp);
}

static char	*delete_line(char **save_read)
{
	char	*new_read;
	int		i;
	int		j;

	if ((*save_read)[0] == '\0')
	{
		free (*save_read);
		return (NULL);
	}
	i = 0;
	while ((*save_read)[i] && (*save_read)[i] != '\n')
		++i;
	if ((*save_read)[i] == '\0')
	{
		free (*save_read);
		return (NULL);
	}
	new_read = (char *) ft_calloc(1, ft_strlen(*save_read, 0) - i + 1);
	j = 0;
	while ((*save_read)[++i])
		new_read[j++] = (*save_read)[i];
	free (*save_read);
	return (new_read);
}

static char	*save_to_line(int fd, char *line, char **save_read, \
ssize_t *read_len)
{
	char	*buf;

	if (!(*save_read) || (*save_read)[0] == '\0')
	{
		buf = (char *) ft_calloc(sizeof(char) * (BUFFER_SIZE + 1), 1);
		*read_len = read(fd, buf, BUFFER_SIZE);
		*save_read = copy_buf(&(*save_read), buf);
		free(buf);
	}
	if (!*save_read)
		return (NULL);
	if (*read_len > 0 || (*save_read)[0] != '\0')
		line = ft_strjoin(line, &(*save_read));
	return (line);
}

static char	*read_fd(int fd, char *line)
{
	ssize_t		read_len;
	static char	*save_read;

	read_len = 0;
	line = save_to_line(fd, line, &save_read, &read_len);
	save_read = delete_line(&save_read);
	if (read_len < 0)
		return (NULL);
	if (!save_read)
		read_len++;
	while (read_len > 0 && !ft_strchr(line, '\n'))
	{
		line = save_to_line(fd, line, &save_read, &read_len);
		save_read = delete_line(&save_read);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	line = read_fd(fd, line);
	return (line);
}
