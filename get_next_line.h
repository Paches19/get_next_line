/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:10:24 by adpachec          #+#    #+#             */
/*   Updated: 2022/10/19 13:20:20 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

# if BUFFER_SIZE > 100000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char const *s2);
void	utils(void);
size_t	ft_strlen(const char *s);

#endif