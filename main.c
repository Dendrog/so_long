/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:41:22 by jakim             #+#    #+#             */
/*   Updated: 2024/05/14 14:43:28 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_stats	g_stat;
static char		**g_map;

static void	re_image(int row, int col, t_vars *vars, int n)
{
	char	*tmp;

	if (g_map[g_stat.row][g_stat.col] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player[6], \
			(g_stat.col) * 50, (g_stat.row) * 50);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player[0], \
			(g_stat.col) * 50, (g_stat.row) * 50);
	ft_printf("%d\n", g_stat.score);
	tmp = ft_itoa(g_stat.score);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player[5], 0, 0);
	mlx_string_put(vars->mlx, vars->win, 20, 30, 0xFF0000, tmp);
	free(tmp);
	g_stat.row += row;
	g_stat.col += col;
	if (g_map[g_stat.row][g_stat.col] != 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player[n], \
			(g_stat.col) * 50, (g_stat.row) * 50);
}

void	move(int row, int col, t_vars *vars, int n)
{
	char	*tmp;

	if (g_map[g_stat.row + row][g_stat.col + col] == '1')
		return ;
	g_stat.score++;
	if (g_map[g_stat.row + row][g_stat.col + col] == 'C')
	{
		g_stat.c--;
		g_map[g_stat.row + row][g_stat.col + col] = '0';
	}
	if (g_map[g_stat.row + row][g_stat.col + col] == 'I')
		exit(0);
	if (g_map[g_stat.row + row][g_stat.col + col] == 'E')
	{
		if (!g_stat.c)
			exit(0);
	}
	re_image(row, col, vars, n);
}

static void	open_textures(void *im[6], t_vars vars)
{
	im[0] = mlx_xpm_file_to_image(vars.mlx, "./textures/grass2.xpm", \
			&width, &height);
	im[1] = mlx_xpm_file_to_image(vars.mlx, "./textures/stone2.xpm", \
			&width, &height);
	im[2] = mlx_xpm_file_to_image(vars.mlx, "./textures/ondia2.xpm", \
			&width, &height);
	im[3] = mlx_xpm_file_to_image(vars.mlx, "./textures/potal2.xpm", \
			&width, &height);
	im[4] = mlx_xpm_file_to_image(vars.mlx, "./textures/front2.xpm", \
			&width, &height);
	im[5] = mlx_xpm_file_to_image(vars.mlx, "./textures/zombie2.xpm", \
			&width, &height);
	vars.player[0] = mlx_xpm_file_to_image(vars.mlx, "./textures/grass2.xpm", \
			&width, &height);
	vars.player[1] = mlx_xpm_file_to_image(vars.mlx, "./textures/front2.xpm", \
			&width, &height);
	vars.player[2] = mlx_xpm_file_to_image(vars.mlx, "./textures/left2.xpm", \
			&width, &height);
	vars.player[3] = mlx_xpm_file_to_image(vars.mlx, "./textures/back2.xpm", \
			&width, &height);
	vars.player[4] = mlx_xpm_file_to_image(vars.mlx, "./textures/right2.xpm", \
			&width, &height);
	vars.player[5] = im[1];
	vars.player[6] = im[3];
}

int	main(int argc, char *argv[])
{
	void	*im[6];
	t_vars	vars;
	int		width;
	int		height;
	int		fd;

	if (argc != 2)
		print_err("Error : no input mapfile\n");
	check_map(argv[1]);
	vars.mlx = mlx_init();
	vars.win = make_window(vars.mlx, argv[1]);
	if (!vars.win)
		print_err("Error : window fail\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_err("Error : mapfile open fail\n");
	g_stat.score = 0;
	map_set(im, fd, vars.mlx, vars.win);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, x_close, &vars);
	mlx_loop(vars.mlx);
}
