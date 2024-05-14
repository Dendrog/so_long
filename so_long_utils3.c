/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:36:26 by jakim             #+#    #+#             */
/*   Updated: 2024/05/14 15:12:11 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void check_entity(t_stats *g_stat, char **g_map)
{
    char    **tmp;
    int e;
    int p;
    int i;

    g_stat->c = 0;
    e = 0;
    p = 0;
    i = 0;
    tmp = g_map;
    while (*tmp)
    {
        if ((*tmp)[i] != '0' && (*tmp)[i] != '1' && (*tmp)[i] != 'C' && (*tmp)[i] != 'E' && (*tmp)[i] != 'P' && (*tmp)[i] != 'I' && (*tmp)[i] != 0 && (*tmp)[i] != '\n')
            print_err("Error : invalid map tile\n");
        if ((*tmp)[i] == 'C')
            g_stat->c++;
        if ((*tmp)[i] == 'E')
            e++;
        if ((*tmp)[i] == 'P')
            p++;
        if ((*tmp)[i] == '\n' || (*tmp)[i] == 0)
        {
            i = 0;
            tmp++;
        }
        else
            i++;
    }
    if (g_stat->c < 1)
        print_err("Error : no collection\n");
    if (e != 1)
        print_err("Error : no one exit\n");
    if (p != 1)
        print_err("Error : no one starting point\n");
}

void    check_wall(t_stats *g_stat, char **g_map)
{
    char    **tmp;
    int i;
    int k;

    i = 0;
    if (g_stat->width < 3 || g_stat->height < 3)
        print_err("Error : not blocked\n");
    tmp = g_map;
    while (tmp[i])
    {
        k = 0;
        if (i == 0 || tmp[i + 1] == NULL)
        {
            while (tmp[i][k])
                if (tmp[i][k++] != '1')
                    print_err("Error : not blocked\n");
        }
        if (tmp[i][0] != '1' || tmp[i][ft_strlen(tmp[i]) - 1] != '1')
            print_err("Error : not blocked\n");
        i++;
    }
}

int dfs_c(char **tmp, int row, int col)
{
    int count;

    count = 0;
    if (tmp[row][col] == '1' || tmp[row][col] == 'I')
        return (0);
    if (tmp[row][col] == 'C' ||tmp[row][col] == 'E')
        count ++;
    tmp[row][col] = '1';
    count += dfs_c(tmp, row + 1, col);
    count += dfs_c(tmp, row - 1, col);
    count += dfs_c(tmp, row, col + 1);
    count += dfs_c(tmp, row, col - 1);
    return (count);
}

void    pre_dfs_one(int row, int col, char **g_map, t_stats *g_stat)
{
    char    **tmp;
    int k;

    k = 0;
    tmp = (char **)malloc(sizeof(char *) * (g_stat->height + 1));
    if (!tmp)
        print_err("Error : allocate fail\n");
    while (g_map[k])
    {
        tmp[k] = ft_strdup(g_map[k]);
        k++;
    }
    tmp[k] = NULL;
    k = dfs_c(tmp, row, col);
    if (k != g_stat->c + 1)
        print_err("Error : no path in map\n");
    free_mem(tmp);
}