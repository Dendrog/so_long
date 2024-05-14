/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:50:36 by jakim             #+#    #+#             */
/*   Updated: 2024/05/14 21:25:20 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	increase(char bit, int *row, int *col)
{
	if (bit == '\n')
	{
		*col = *col + 50;
		*row = 0;
	}
	else
		*row += 50;
}

void	map_set(void *im[], int fd, void *ptr, void *wind)
{
	char	bit;
	int		row;
	int		col;

	row = 0;
	col = 0;
	while (read(fd, &bit, 1))
	{
		if (bit == '0')
			mlx_put_image_to_window(ptr, wind, im[0], row, col);
		else if (bit == '1')
			mlx_put_image_to_window(ptr, wind, im[1], row, col);
		else if (bit == 'C')
			mlx_put_image_to_window(ptr, wind, im[2], row, col);
		else if (bit == 'E')
			mlx_put_image_to_window(ptr, wind, im[3], row, col);
		else if (bit == 'P')
			mlx_put_image_to_window(ptr, wind, im[4], row, col);
		else if (bit == 'I')
			mlx_put_image_to_window(ptr, wind, im[5], row, col);
		increase(bit, &row, &col);
	}
}

int	check_mapname(char *mapname)
{
	char	*start;

	start = ft_strnstr(mapname, ".ber", 255);
	if (start == NULL)
		return (0);
	if (!ft_strncmp(start, ".ber", ft_strlen(start)))
		return (1);
	return (0);
}

int	check_rectangle(char *mapname, int width)
{
	char	buf;
	char	tmp;
	int		fd;
	int		n;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		print_err("Error : mapfile open fail\n");
	n = 0;
	while (1)
	{
		if (read(fd, &buf, 1) <= 0)
			break ;
		tmp = buf;
		if (buf == '\n')
		{
			if (width)
				if (width != n)
					return (0);
			width = n;
			n = 0;
			continue ;
		}
		else
			n++;
	}
	if (width)
		if (width != n)
			return (0);
	return (1);
}
