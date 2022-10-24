/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:42:50 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/24 19:49:30 by adpachec         ###   ########.fr       */
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

char	*write_last(char *str, int len_s1, const char *s2, int i)
{
	if (s2[len_s1 + i] == '\n')
	{
		str[len_s1 + i] = s2[i];
		str[len_s1 + i + 1] = '\0';
		return (str);
	}
	else
	{
		str[len_s1 + i] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char const **s2)
{
	char			*str;
	int				i;
	const size_t	len_s1 = ft_strlen(s1);
	const size_t	len_s2 = ft_strlen_gnl(*s2);

	str = (char *) ft_calloc(sizeof(char) * (len_s1 + len_s2 + 2), 1);
	if (!str)
	{
		if (s1)
			return (s1);
		return (NULL);
	}
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	i = -1;
	while (*s2[++i] && *s2[i] != '\n')
		str[len_s1 + i] = *s2[i];
	write_last(str, len_s1, *s2, i);
	return (str);
}

char	*copy_buf(char **save_read, char *buf)
{
	int		i;
	int		j;
	char	*temp;

	temp = (char *) ft_calloc(ft_strlen(*save_read) + ft_strlen(buf) + 1, 1);
	i = 0;
	while (temp[i])
		++i;
	j = -1;
	while (buf[++j])
		temp[i++] = buf[j];
	temp[i] = '\0';
	free (*save_read);
	return (temp);
}

char	*delete_line(char **save_read)
{
	char	*new_read;
	int		len;
	int		i;
	int		j;

	printf("\nsr delete: %s", *save_read);
	i = 0;
	while (*save_read[i] && *save_read[i] != '\n')
		++i;
	len = ft_strlen(*save_read) - i;
	new_read = (char *) ft_calloc(1, len + 1);
	j = 0;
	while (*save_read[++i])
		new_read[j++] = *save_read[i];
	printf("\ndelete: %s", new_read);
	free(*save_read);
	return (new_read);
}

char	*save_to_line(int fd, char *line, char **save_read, ssize_t *read_len)
{
	char	*buf;

	if (!ft_strlen(*save_read))
	{
		buf = (char *) ft_calloc(sizeof(char) * (BUFFER_SIZE + 2), 1);
		*read_len = read(fd, buf, BUFFER_SIZE);
		*save_read = copy_buf(&(*save_read), buf);
		free(buf);
	}
	if (!*save_read)
		return (NULL);
	printf("\nsr stl: %s", *save_read);
	if (*read_len > 0)
		line = ft_strjoin(line, &save_read);
	printf("\nline: %s", line);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_fd(int fd, char *line)
{
	ssize_t		read_len;
	static char	*save_read;

	read_len = 0;
	line = save_to_line(fd, line, &save_read, &read_len);
	printf("\nline rfd: %s", line);
	printf("\nsr rfd: %s", save_read);
	save_read = delete_line(save_read);
	printf("\nsr rfd: %s", save_read);
	if (read_len <= 0)
		return (NULL);
	while (read_len > 0 && !ft_strchr(save_read, '\n') && \
	*save_read != '\0')
	{
		line = save_to_line(fd, line, save_read, &read_len);
		save_read = delete_line(line);
		printf("\nsrlast: %s", save_read);
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
	printf("\nline last: %s", line);
	return (line);
}

int	main()
{
	int fd;

	fd = open("fd.txt", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
}
