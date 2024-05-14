/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:38:10 by jakim             #+#    #+#             */
/*   Updated: 2024/05/14 14:43:20 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    check_path(t_stats g_stat)
{
    char    **ptr;
    int k;
    int i;

    k = 0;
    ptr = g_map;
    while (ptr[k])
    {
        i = 0;
        while (ptr[k][i])
        {
            if (ptr[k][i] == 'P')
            {
                g_stat.row = k;
                g_stat.col = i;
                pre_dfs_one(k, i);
                return ;
            }
            i++;
        }
        k++;
    }
}

int key_hook(int key, t_vars *vars) // w=119 a=97 s=115 d=100
{
	if (key == 65307)
        exit(0);
    if(key == 119) // w
        move(-1,0,vars,3);
    if(key == 97) // a
        move(0,-1,vars,2);
    if(key == 115) // s
        move(1,0,vars,1);
    if(key == 100) // d
        move(0,1,vars,4);
    return 0;
}

int	x_close()
{
	exit(0);
}