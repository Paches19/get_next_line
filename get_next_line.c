/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:42:50 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/26 12:14:32 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	const size_t	len = count * size;
	size_t			i;

	if (!count)
		return (malloc(0));
	if (len / count != size)
		return (NULL);
	ptr = (char *) malloc(len);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && len > 0)
	{
		ptr[i] = 0;
		++i;
	}
	return (ptr);
}

size_t	ft_strlen(char *s, int gnl)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	if (!gnl)
	{
		while (s[len])
			++len;
	}
	else
	{
		while (s[len] && s[len] != '\n')
			++len;
	}
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	if (!s || !c)
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

char	*write_last(char **str, int len_s1, char s2, int i)
{
	if (s2 == '\n')
		(*str)[len_s1 + i] = s2;
	return (*str);
}

char	*ft_strjoin(char *line, char **save_read)
{
	char			*str;
	int				i;
	const size_t	len_line = ft_strlen(line, 0);
	const size_t	len_save_read = ft_strlen(*save_read, 1);

	//printf("\nlen1: %zu", len_line);
	//printf("\nlen2: %zu", len_save_read);
	if (!(*save_read)[0])
	{
		free (*save_read);
		return (line);
	}
	str = (char *) ft_calloc(sizeof(char) * (len_line + len_save_read + 2), 1);
	if (!str)
	{
		if (line)
			return (line);
		return (NULL);
	}
	i = -1;
	if (line)
	{
		while (line[++i])
			str[i] = line[i];
	}
	i = -1;
	while ((*save_read)[++i] && (*save_read)[i] != '\n')
		str[len_line + i] = (*save_read)[i];
	//printf("\nsave_read: %d", (*save_read)[i]);
	write_last(&str, len_line, (*save_read)[i], i);
	free (line);
	return (str);
}

char	*copy_buf(char **save_read, char *buf)
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

char	*delete_line(char **save_read)
{
	char	*new_read;
	int		len;
	int		i;
	int		j;

	//printf("\nsr delete: %s", *save_read);
	if ((*save_read)[0] == '\0')
	{
		//printf("\ndevuevlo null");
		free (*save_read);
		return (NULL);
	}
	i = 0;
	while ((*save_read)[i] && (*save_read)[i] != '\n')
		++i;
	//printf("\ni: %d", i);
	if ((*save_read)[i] == '\0')
	{
		//printf("\ndevuevlo null");
		free (*save_read);
		return (NULL);
	}
	len = ft_strlen(*save_read, 0) - i;
	new_read = (char *) ft_calloc(1, len + 1);
	j = 0;
	while ((*save_read)[++i])
		new_read[j++] = (*save_read)[i];
	//printf("\ndelete: %d", new_read[0]);
	free (*save_read);
	return (new_read);
}

char	*save_to_line(int fd, char *line, char **save_read, ssize_t *read_len)
{
	char	*buf;

	if (!(*save_read) || (*save_read)[0] == '\0')
	{
		//printf("\nnew save read\n");
		buf = (char *) ft_calloc(sizeof(char) * (BUFFER_SIZE + 1), 1);
		*read_len = read(fd, buf, BUFFER_SIZE);
		*save_read = copy_buf(&(*save_read), buf);
		//printf("\nsr new: %s", *save_read);
		free(buf);
	}
	if (!*save_read)
		return (NULL);
	//printf("\nsr stl: %d", (*save_read)[0]);
	if (*read_len > 0 || (*save_read)[0] != '\0')
		line = ft_strjoin(line, &(*save_read));
	//printf("\nline: %d", line[0]);
	return (line);
}

char	*read_fd(int fd, char *line)
{
	ssize_t		read_len;
	static char	*save_read;
	int			i;

	read_len = 0;
	line = save_to_line(fd, line, &save_read, &read_len);
	//printf("\nline rfd: %s", line);
	//printf("\nread_len: %zd", read_len);
	save_read = delete_line(&save_read);
	//printf("\nsr rfd2: %s", save_read);
	if (read_len < 0)
		return (NULL);
	if (!save_read)
		read_len++;
	i = -1;
	while (read_len > 0 && !ft_strchr(line, '\n'))
	{
		line = save_to_line(fd, line, &save_read, &read_len);
		//printf("\nline postwhile: %s", line);
		save_read = delete_line(&save_read);
		//printf("\nsrlast: %s", save_read);
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
	//printf("\nline last:\n%s", line);
	return (line);
}

// int	main()
// {
// 	int fd;

// 	fd = open("variable_nls.txt", O_RDONLY);
// 	get_next_line(fd);
// 	get_next_line(fd);
// 	get_next_line(fd);
// 	get_next_line(fd);
// 	get_next_line(fd);
// 	get_next_line(fd);
// 	get_next_line(fd);
// 	//get_next_line(fd);
// }
