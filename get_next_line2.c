/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:11:04 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/20 10:11:04 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *) s;
	i = 0;
	while (i < n && n > 0)
	{
		ptr[i] = 0;
		++i;
	}
}

static char	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	const size_t	len = count * size;

	if (!count)
		return (malloc(0));
	if (len / count != size)
		return (NULL);
	ptr = (char *) malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

static size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] && s[len] != '\n')
		++len;
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		++len;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		++i;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen_gnl(s2);
	str = (char *) ft_calloc(sizeof(char) * (len_s1 + len_s2 + 2), 1);
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	i = -1;
	while (s2[++i] && s2[i] != '\n' && s2[i] != '\0')
	{
		str[len_s1 + i] = s2[i];
	}
	if (s2[i++] == '\n')
		str[len_s1 + i - 1] = '\n';
	str[len_s1 + i] = '\0';
	return (str);
}
char	*buf_to_line(int fd, char *line, char *buf, ssize_t *read_len)
{
	buf = (char *) ft_calloc(sizeof(char) * (BUFFER_SIZE + 1), 1);
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	*read_len = read(fd, buf, BUFFER_SIZE);
	if (*read_len > 0)
		line = ft_strjoin(line, buf);
	else
	{
		free(buf);
		return (line);
	}
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
char	*read_fd(int fd, char *line)
{
	ssize_t	read_len;
	char	*buf;

	buf = NULL;
	read_len = 0;
	line = buf_to_line(fd, line, buf, &read_len);
	if (read_len <= 0)
		return (NULL);
	while (read_len > 0 && !ft_strchr(buf,'\n') && !ft_strchr(buf,'\0'))
	{
		free(buf);
		line = buf_to_line(fd, line, buf, &read_len);
	}
	if (buf)
		free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_fd(fd, line);
	return (line);
}