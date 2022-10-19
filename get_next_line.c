/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:05:31 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/19 17:04:11 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (1);
		++i;
	}
	if (c == '\0')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s || s[0] == 0)
		return (0);
	len = 0;
	while (s[len])
		++len;
	return (len);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return ((char *) s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *) malloc(len_s1 + len_s2 + 2);
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	i = -1;
	while (++i < BUFFER_SIZE && s2[i] != '\n' && s2[i] != '\0')
		str[len_s1 + i] = s2[i];
	if (s2[i++] == '\n')
	{
		str[len_s1 + i - 1] = s2[i - 1];
		str[len_s1 + i] = '\0';
	}
	else
	{
		if (i < 0)
			i = 0;
		--i;
		str[len_s1 + i] = '\0';
	}
	return (str);
}

int	read_fd(int fd, char *line)
{
	char	*buf;
	ssize_t	read_len;

	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	read_len = read(fd, buf, BUFFER_SIZE);
	buf[BUFFER_SIZE] = '\0';
	if (read_len > 0)
		line = ft_strjoin(line, buf);
	while (read_len > 0 && \
	(!ft_strchr((char const *) buf, '\n') || \
	!ft_strchr((char const *) buf, '\0')))
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
		// printf("\nbuf: %s\n", buf);
		// printf("\nline: %s\n", line);
		if (read_len > 0)
		{
			line = ft_strjoin(line, buf);
			// printf("\nline: %s", line);
		}
	}
	free(buf);
	return (read_len);
}

char	*get_next_line(int fd)
{
	static char	*line;
	ssize_t		read_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_len = read_fd(fd, line);
	if (read_len < 0 && read_len != 42)
		free(line);
	return (line);
}

// int	main()
// {
// 	int fd;

// 	fd = open("vacio.txt", O_RDONLY);
// 	get_next_line(fd);
// }
