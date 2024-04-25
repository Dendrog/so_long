#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include "./get_next_line/get_next_line.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
    void    *player[5];
}				t_vars;

typedef struct	s_stats {
	int row;
    int col;
    int score;
    int c;
    int width;
    int height;
}				t_stats;

static t_stats  g_stat;

static char **g_map;

void    print_err(char *s)
{
    ft_printf("%s",s);
    exit(1);
}

void map_set(void *im[], int fd, void *ptr, void *wind)
{
    char bit;
    int row;
    int col;

    row = 0;
    col = 0;
    while (read(fd, &bit, 1))
    {
        if (bit == '0')
            mlx_put_image_to_window(ptr, wind, im[0], row, col);
        else if (bit == '1')
            mlx_put_image_to_window(ptr, wind, im[1], row, col);
        else if (bit == 'C')
        {
            mlx_put_image_to_window(ptr, wind, im[0], row, col);
            mlx_put_image_to_window(ptr, wind, im[2], row, col);
        }
        else if (bit == 'E')
            mlx_put_image_to_window(ptr, wind, im[3], row, col);
        else if (bit == 'P'){
            mlx_put_image_to_window(ptr, wind, im[0], row, col);
            mlx_put_image_to_window(ptr, wind, im[4], row, col);
        }
        if (bit == '\n')
        {
            col = col + 50;
            row = 0;
        }
        else
            row += 50;
    }
}

int check_mapname(char *mapname)
{
    char    *start;

    start = ft_strnstr(mapname, ".ber", 255);
    if (start == NULL)
        return (0);
    if (!ft_strncmp(start, ".ber", ft_strlen(start)))
        return (1);
    return (0);
}

int check_rectangle(char *mapname, int width)
{
    char    buf;
    char    tmp;
    int fd;
    int n;

    fd = open(mapname, O_RDONLY);
    if (fd < 0 )
        print_err("Error : mapfile open fail\n");
    n = 0;
    while (1)
    {
        if (read(fd, &buf, 1) <= 0)
            break;
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

void    set_wh(char *mapname)
{
    int fd;
    char    buf;
    int flag;

    fd = open(mapname, O_RDONLY);
    if (fd < 0 )
        print_err("Error : mapfile open fail\n");
    g_stat.width = 0;
    g_stat.height = 1;
    flag = 0;
    while (1)
    {
        if (read(fd, &buf, 1) <= 0)
            break;
        if (buf == '\n')
        {
            flag = 1;
            g_stat.height++;
        }
        if (flag == 0)
            g_stat.width++;
    }
    if (g_stat.width == 0)
        print_err("Error : map is empty\n");
    close(fd);
}

void    map_to_array(char *mapname)
{
    char    *tmp;
    char    *chr;
    char    **m;
    int fd;

    set_wh(mapname);
    fd = open(mapname, O_RDONLY);
    if (fd < 0)
        print_err("Error : mapfile open fail\n");
    g_map = (char **)malloc(sizeof(char *) * (g_stat.height + 1));
    if (!g_map)
        print_err("Error : allocate fail\n");
    m = g_map;
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
    g_stat.width = ft_strlen(*g_map);
}

void check_entity()
{
    char    **tmp;
    int e;
    int p;
    int i;

    g_stat.c = 0;
    e = 0;
    p = 0;
    i = 0;
    tmp = g_map;
    while (*tmp)
    {
        if ((*tmp)[i] != '0' && (*tmp)[i] != '1' && (*tmp)[i] != 'C' && (*tmp)[i] != 'E' && (*tmp)[i] != 'P' && (*tmp)[i] != 0 && (*tmp)[i] != '\n')
            print_err("Error : invalid map tile\n");
        if ((*tmp)[i] == 'C')
            g_stat.c++;
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
    if (g_stat.c < 1)
        print_err("Error : no collection\n");
    if (e != 1)
        print_err("Error : no one exit\n");
    if (p != 1)
        print_err("Error : no one starting point\n");
}

void    check_wall()
{
    char    **tmp;
    int i;
    int k;

    i = 0;
    if (g_stat.width < 3 || g_stat.height < 3)
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

void    free_mem(char **tmp)
{
    char    **ptr;

    ptr = tmp;
    while (*ptr)
    {
        free(*ptr);
        ptr++;
    }
    free(tmp);
}

int dfs_c(char **tmp, int row, int col)
{
    int count;

    count = 0;
    if (tmp[row][col] == '1' || tmp[row][col] == 'E' || tmp[row][col] == 'V')
        return (0);
    if (tmp[row][col] == 'C')
        count ++;
    tmp[row][col] = 'V';
    count += dfs_c(tmp, row + 1, col);
    count += dfs_c(tmp, row - 1, col);
    count += dfs_c(tmp, row, col + 1);
    count += dfs_c(tmp, row, col - 1);
    return (count);
}

int dfs_e(char **tmp, int row, int col)
{
    int count;

    count = 0;
    if (tmp[row][col] == '1')
        return (0);
    if (tmp[row][col] == 'E')
        count ++;
    tmp[row][col] = '1';
    count += dfs_e(tmp, row + 1, col);
    count += dfs_e(tmp, row - 1, col);
    count += dfs_e(tmp, row, col + 1);
    count += dfs_e(tmp, row, col - 1);
    return (count);
}

void    pre_dfs_one(int row, int col)
{
    char    **tmp;
    int k;

    k = 0;
    tmp = (char **)malloc(sizeof(char *) * (g_stat.height + 1));
    if (!tmp)
        print_err("Error : allocate fail\n");
    while (g_map[k])
    {
        tmp[k] = ft_strdup(g_map[k]);
        k++;
    }
    tmp[k] = NULL;
    k = dfs_c(tmp, row, col) + dfs_e(tmp, row, col);
    if (k != g_stat.c + 1)
        print_err("Error : no path in map\n");
    free_mem(tmp);
    //return (k);
}

void    check_path()
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

void    check_map(char *mapname)
{
    int fd;

    fd = open(mapname, O_RDONLY);
    if (fd < 0)
        print_err("Error : mapfile open fail\n");
    if (!check_mapname(mapname))
        print_err("Error : mapname is not valid\n");
    if (!check_rectangle(mapname, 0))
        print_err("Error : map is not rectangle\n");
    map_to_array(mapname);
    check_entity();
    check_wall();
    check_path();
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

void    move(int row, int col, t_vars *vars, int n)
{
    if (g_map[g_stat.row + row][g_stat.col + col] == '1')
        return ;
    g_stat.score++;
    if (g_map[g_stat.row + row][g_stat.col + col] == 'C')
    {
        g_stat.c--;
        g_map[g_stat.row + row][g_stat.col + col] = '0';
    }
    if (g_map[g_stat.row + row][g_stat.col + col] == 'E')
    {
        if (g_stat.c)
            return ;
        exit(0);
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->player[0], (g_stat.col) * 50, (g_stat.row) * 50);
    ft_printf("%d\n", g_stat.score);
    g_stat.row += row;
    g_stat.col += col;
    mlx_put_image_to_window(vars->mlx, vars->win, vars->player[n], (g_stat.col) * 50, (g_stat.row) * 50);
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

int main(int argc, char *argv[]){
    t_vars  vars;
    void    *im[5];
    int width;
    int height;
    int fd;

    if (argc != 2)
        print_err("Error : no input mapfile\n");
    check_map(argv[1]);
    vars.mlx = mlx_init();
    vars.win = make_window(vars.mlx, argv[1]);
    if (!vars.win)
        print_err("Error : window fail\n");
    im[0] = mlx_xpm_file_to_image ( vars.mlx, "./textures/grass2.xpm", &width, &height);
    im[1] = mlx_xpm_file_to_image ( vars.mlx, "./textures/stone2.xpm", &width, &height);
    im[2] = mlx_xpm_file_to_image ( vars.mlx, "./textures/ondia2.xpm", &width, &height);
    im[3] = mlx_xpm_file_to_image ( vars.mlx, "./textures/potal2.xpm", &width, &height);
    im[4] = mlx_xpm_file_to_image ( vars.mlx, "./textures/front2.xpm", &width, &height); //steve
    vars.player[0] = mlx_xpm_file_to_image ( vars.mlx, "./textures/grass2.xpm", &width, &height);
    vars.player[1] = mlx_xpm_file_to_image ( vars.mlx, "./textures/front2.xpm", &width, &height);
    vars.player[2] = mlx_xpm_file_to_image ( vars.mlx, "./textures/left2.xpm", &width, &height);
    vars.player[3] = mlx_xpm_file_to_image ( vars.mlx, "./textures/back2.xpm", &width, &height);
    vars.player[4] = mlx_xpm_file_to_image ( vars.mlx, "./textures/right2.xpm", &width, &height);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        print_err("Error : mapfile open fail\n");
    g_stat.score = 0;
    map_set(im, fd, vars.mlx, vars.win);
    mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, x_close, &vars);
    mlx_loop(vars.mlx);
}