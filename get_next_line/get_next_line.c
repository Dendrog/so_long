/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:50:35 by jakim             #+#    #+#             */
/*   Updated: 2024/03/19 21:07:35 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_save(char	**save, char **ptr, char **pre, int *size)
{
	int	tmp;

	if (*save)
	{
		tmp = ft_strchrs(*save, '\n');
		ft_strncat(*ptr, *save, tmp + 1);
		if (tmp < (int)ft_strlen2(*save))
		{
			free(*pre);
			(*pre) = (*save);
			*save = ft_substr(*pre, tmp + 1, BUFFER_SIZE);
			free(*pre);
			return (1);
		}
		(*size) += BUFFER_SIZE;
		*ptr = ft_strdup2(*ptr, *size);
		free(*save);
		(*save) = NULL;
	}
	return (0);
}

int	make_string(char **save, char **ptr, char **pre, int fd)
{
	int	tmp;

	tmp = read(fd, *pre, BUFFER_SIZE);
	if (!(**ptr) && !(*save) && tmp <= 0)
	{
		free(*pre);
		free(*ptr);
		(*ptr) = NULL;
		return (-1);
	}
	(*pre)[tmp] = 0;
	tmp = ft_strchrs(*pre, '\n');
	ft_strncat(*ptr, *pre, tmp + 1);
	if (tmp < BUFFER_SIZE)
	{
		*save = ft_substr(*pre, tmp + 1, BUFFER_SIZE);
		free(*pre);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*ptr;
	char			*pre;
	int				size;

	ptr = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	size = BUFFER_SIZE;
	pre = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!pre)
		return (NULL);
	while (1)
	{
		ptr = ft_strdup2(ptr, size);
		if (check_save(&save, &ptr, &pre, &size))
			break ;
		if (make_string(&save, &ptr, &pre, fd))
			break ;
		size += BUFFER_SIZE;
	}
	return (ptr);
}
