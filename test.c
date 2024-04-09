#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"

void map_set(void *im[], int fd, void *ptr, void *wind)
{
    char bit;
    int raw=0;
    int col=0;

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
            raw+=50;
    }
}

int main(){
    void    *ptr;
    void    *wind;
    void    *im[5];
    int width = 10;
    int height = 10;
    int fd;
    ptr = mlx_init();
    wind = mlx_new_window(ptr, 1600, 960, "so_long");
    if(!wind)
    {
        perror("Error");
        exit(1);
    }
    im[0] = mlx_xpm_file_to_image ( ptr, "./textures/grass2.xpm", &width, &height);
    im[1] = mlx_xpm_file_to_image ( ptr, "./textures/stone2.xpm", &width, &height);
    im[2] = mlx_xpm_file_to_image ( ptr, "./textures/ondia2.xpm", &width, &height);
    im[3] = mlx_xpm_file_to_image ( ptr, "./textures/potal2.xpm", &width, &height);
    im[4] = mlx_xpm_file_to_image ( ptr, "./textures/steve2.xpm", &width, &height); //steve
    fd = open("./maps/testmap.ber",O_RDONLY);
    map_set(im, fd, ptr, wind);
    //mlx_put_image_to_window(ptr, wind, im, 50, 50);
    mlx_loop(ptr);
}