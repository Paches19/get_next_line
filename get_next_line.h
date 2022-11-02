/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:10:24 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/02 12:25:22 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
#include "fcntl.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE > 1000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *line, char **save_read);
char	*ft_memcpy(char *dst, char *src);
int		ft_strchr(char *s, int c);
size_t	ft_strlen(char *s, int gnl);
char	*ft_calloc(size_t count, size_t size);
char	*write_line(char *line, char **save_read);

#endif