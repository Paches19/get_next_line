/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:15:14 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/26 16:45:48 by adpachec         ###   ########.fr       */
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

	if (!(*save_read)[0])
	{
		free (*save_read);
		return (line);
	}
	str = (char *) ft_calloc(sizeof(char) * (len_line + len_save_read + 2), 1);
	if (!str)
		return (NULL);
	i = -1;
	if (line)
	{
		while (line[++i])
			str[i] = line[i];
	}
	i = -1;
	while ((*save_read)[++i] && (*save_read)[i] != '\n')
		str[len_line + i] = (*save_read)[i];
	write_last(&str, len_line, (*save_read)[i], i);
	free (line);
	return (str);
}
