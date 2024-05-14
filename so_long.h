/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 22:22:40 by jakim             #+#    #+#             */
/*   Updated: 2024/05/14 14:43:26 by jakim            ###   ########.fr       */
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

void	move(int row, int col, t_vars *vars, int n)
void	print_err(char *s)
void	map_set(void *im[], int fd, void *ptr, void *wind)
int		check_mapname(char *mapname)
int		check_rectangle(char *mapname, int width)
void	free_mem(char **tmp)
void	check_map(char *mapname)
void	*make_window(void *ptr, char *mapname)
void	set_wh(char *mapname, t_stats g_stat)
void	map_to_array(char *mapname, t_stats g_stat)
void	check_entity(t_stats g_stat)
void	check_wall(t_stats g_stat)
int		dfs_c(char **tmp, int row, int col)
void	pre_dfs_one(int row, int col, char **g_map, t_stats g_stat)
void	check_path(t_stats g_stat)
int		key_hook(int key, t_vars *vars)
int		x_close()

#endif
