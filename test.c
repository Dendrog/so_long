#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void    print_err(char *s)
{
    ft_printf("%s",s);
    exit(1);
}

void map_set(void *im[], int fd, void *ptr, void *wind)
{
    char bit;
    int raw;
    int col;

    raw = 0;
    col = 0;
    while (read(fd, &bit, 1))
    {
        if (bit == '0')
            mlx_put_image_to_window(ptr, wind, im[0], raw, col);
        else if (bit == '1')
            mlx_put_image_to_window(ptr, wind, im[1], raw, col);
        else if (bit == 'C')
        {
            mlx_put_image_to_window(ptr, wind, im[0], raw, col);
            mlx_put_image_to_window(ptr, wind, im[2], raw, col);
        }
        else if (bit == 'E')
            mlx_put_image_to_window(ptr, wind, im[3], raw, col);
        else if (bit == 'P'){
            mlx_put_image_to_window(ptr, wind, im[0], raw, col);
            mlx_put_image_to_window(ptr, wind, im[4], raw, col);
        }
        if (bit == '\n')
        {
            col = col + 50;
            raw = 0;
        }
        else
            raw += 50;
    }
}

void    check_map(char *mapname)
{
    int fd;

    fd = open(mapname, O_RDONLY);
    if (fd < 0 )
        print_err("Error : mapfile open fail\n");
    
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

int	esc_close(int key)//, t_vars var)
{
	if (key == 65307)
        exit(0);
	return (0);
}

int main(int argc, char *argv[]){
    t_vars  vars;
    void    *im[5];
    int width;
    int height;
    int fd;

    if (argc != 2)
        print_err("Error : no input mapfile\n");
    vars.mlx = mlx_init();
    vars.win = make_window(vars.mlx, argv[1]);
    if (!vars.win)
        print_err("Error : window fail\n");
    im[0] = mlx_xpm_file_to_image ( vars.mlx, "./textures/grass2.xpm", &width, &height);
    im[1] = mlx_xpm_file_to_image ( vars.mlx, "./textures/stone2.xpm", &width, &height);
    im[2] = mlx_xpm_file_to_image ( vars.mlx, "./textures/ondia2.xpm", &width, &height);
    im[3] = mlx_xpm_file_to_image ( vars.mlx, "./textures/potal2.xpm", &width, &height);
    im[4] = mlx_xpm_file_to_image ( vars.mlx, "./textures/front2.xpm", &width, &height); //steve
    fd = open(argv[1], O_RDONLY);
    if (fd < 0 )
        print_err("Error : mapfile open fail\n");
    map_set(im, fd, vars.mlx, vars.win);
    mlx_key_hook(vars.win, esc_close, &vars);
    //mlx_key_hook(vars.win, esc_close, &vars);
    mlx_loop(vars.mlx);
}