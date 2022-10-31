/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:15:14 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/31 13:45:36 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	const size_t	len = count * size;
	size_t			i;

	if (!count)
		return (malloc(0));
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

	if (!s)
		return (0);
	len = 0;
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

int	ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] == (char) c)
			return (1);
	}
	return (0);
}

void	write_last(char **str, int len_s1, char s2, int i)
{
	if (s2 == '\n')
		(*str)[len_s1 + i] = s2;
}

char	*ft_strjoin(char *line, char **save_read)
{
	char			*str;
	int				i;
	const size_t	len_line = ft_strlen(line, 0);
	const size_t	len_save_read = ft_strlen(*save_read, 1);

	if (BUFFER_SIZE < 5)
	{
		if (!line)
			line = (char *) ft_calloc(sizeof(char) * (50000 + 2), 1);
		if (!line)
			return (NULL);
		return (write_line(line, &(*save_read)));
	}
	str = (char *) ft_calloc(1, sizeof(char) * (len_line + len_save_read + 2));
	if (!str)
		return (NULL);
	i = -1;
	if (line)
	{
		while (line[++i])
			str[i] = line[i];
	}
	str = write_line(str, &(*save_read));
	free (line);
	return (str);
}
