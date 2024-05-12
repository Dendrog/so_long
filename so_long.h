/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:22:40 by jakim             #+#    #+#             */
/*   Updated: 2024/05/12 23:43:36 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include "./get_next_line/get_next_line.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
    void    *player[7];
}				t_vars;

typedef struct	s_stats {
	int row;
    int col;
    int score;
    int c;
    int width;
    int height;
}				t_stats;

#endif
