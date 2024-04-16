/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:50:40 by jakim             #+#    #+#             */
/*   Updated: 2024/03/19 19:28:43 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen2(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strchrs(const char *s, int c);
char	*ft_strdup2(const char *s, int len);
char	*ft_strncat(char *s1, char *s2, int n);
char	*get_next_line(int fd);

#endif
