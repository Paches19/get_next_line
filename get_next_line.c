/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:42:50 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/31 13:48:25 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*write_line(char *line, char **save_read)
{
	char			*str;
	int				j;
	int				i;
	const size_t	len_line = ft_strlen(line, 0);

	j = -1;
	if (BUFFER_SIZE < 5 && !line)
	{
		str = (char *) ft_calloc(sizeof(char) * (50000 + 2), 1);
		while ((*save_read)[++j])
			str[j] = (*save_read)[j];
		return (str);
	}
	else if (BUFFER_SIZE < 5)
	{
		while ((*save_read)[++j] && (*save_read)[j] != '\n')
			line[len_line + j] = (*save_read)[j];
		write_last(&line, len_line, (*save_read)[j], j);
		return (line);
	}
	i = -1;
	while ((*save_read)[++i] && (*save_read)[i] != '\n')
		line[len_line + i] = (*save_read)[i];
	write_last(&line, len_line, (*save_read)[i], i);
	return (line);
}

static char	*delete_line(char **save_read)
{
	char	*new_read;
	int		i;
	int		j;

	if (BUFFER_SIZE == 1)
	{
		free (*save_read);
		return (NULL);
	}
	i = 0;
	while ((*save_read)[i] && (*save_read)[i] != '\n')
		++i;
	if ((*save_read)[i] == '\0' || (*save_read)[0] == '\0')
	{
		free (*save_read);
		return (NULL);
	}
	new_read = (char *) ft_calloc(1, BUFFER_SIZE + 1 - i + 1);
	j = 0;
	while ((*save_read)[++i])
		new_read[j++] = (*save_read)[i];
	free (*save_read);
	return (new_read);
}

static char	*save_to_line(int fd, char *line, char **save_read, \
ssize_t *read_len)
{
	if (!(*save_read) || (*save_read)[0] == '\0')
	{
		free (*save_read);
		*save_read = (char *) ft_calloc(sizeof(char) * (BUFFER_SIZE + 1), 1);
		if (!*save_read)
			return (NULL);
		*read_len = read(fd, *save_read, BUFFER_SIZE);
	}
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
	if (!save_read)
		read_len++;
	if (ft_strchr(line, '\n'))
		return (line);
	while (read_len > 0)
	{
		line = save_to_line(fd, line, &save_read, &read_len);
		if (ft_strchr(save_read, '\n'))
		{
			save_read = delete_line(&save_read);
			return (line);
		}
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
