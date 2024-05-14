/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:23:39 by jakim             #+#    #+#             */
/*   Updated: 2024/05/14 15:14:01 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    check_map(char *mapname, t_stats *g_stat, char ***g_map)
{
    int fd;

    fd = open(mapname, O_RDONLY);
    if (fd < 0)
        print_err("Error : mapfile open fail\n");
    if (!check_mapname(mapname))
        print_err("Error : mapname is not valid\n");
    if (!check_rectangle(mapname, 0))
        print_err("Error : map is not rectangle\n");
    map_to_array(mapname, g_stat, g_map);
    check_entity(g_stat, *g_map);
    check_wall(g_stat, *g_map);
    check_path(g_stat, *g_map);
    close(fd);
}

void    *make_window(void *ptr, char *mapname)
{
    int fd;
    int width;
    int height;
    char    buf;
    int flag;

    fd = open(mapname, O_RDONLY);
    if (fd < 0 )
        print_err("Error : mapfile open fail\n");
    width = 0;
    height = 1;
    flag = 0;
    while (1)
    {
        if (read(fd, &buf, 1) <= 0)
            break;
        if (buf == '\n')
        {
            flag = 1;
            height++;
        }
        if (flag == 0)
            width++;
    }
    close(fd);
    return (mlx_new_window(ptr, width * 50, height * 50, "so_long"));
}

void    set_wh(char *mapname, t_stats *g_stat)
{
    int fd;
    char    buf;
    int flag;

    fd = open(mapname, O_RDONLY);
    if (fd < 0 )
        print_err("Error : mapfile open fail\n");
    g_stat->width = 0;
    g_stat->height = 1;
    flag = 0;
    while (1)
    {
        if (read(fd, &buf, 1) <= 0)
            break;
        if (buf == '\n')
        {
            flag = 1;   
            g_stat->height++;
        }
        if (flag == 0)
            g_stat->width++;
    }
    if (g_stat->width == 0)
        print_err("Error : map is empty\n");
    close(fd);
}

void    map_to_array(char *mapname, t_stats *g_stat, char ***g_map)
{
    char    *tmp;
    char    *chr;
    char    **m;
    int fd;

    set_wh(mapname, g_stat);
    fd = open(mapname, O_RDONLY);
    if (fd < 0)
        print_err("Error : mapfile open fail\n");
    *g_map = (char **)malloc(sizeof(char *) * (g_stat->height + 1));
    if (!(*g_map))
        print_err("Error : allocate fail\n");
    m = *g_map;
    while (1)
    {
        tmp = get_next_line(fd);
        if (tmp == NULL)
            break;
        chr = ft_strchr(tmp, '\n');
        if (chr)
            *chr = 0;
        *(m++) = tmp;
    }
    *m = NULL;
    g_stat->width = ft_strlen(**g_map);
}