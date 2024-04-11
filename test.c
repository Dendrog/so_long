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
    int raw=500;
    int col=400;

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
            raw = 500;
        }
        else
            raw+=50;
    }
}

void    clear_back(void *im)
{
    unsigned int    *p;
    int bpp;
    int line;
    int endian;

    p = (unsigned int *)mlx_get_data_addr(im, &bpp, &line, &endian);
    printf("%d\n",endian);
    printf("%d", line);
    for(int i=100;i<150; i++)
    {
        //write(1, &p[i],1);
        printf("%X\n",p[i]);
    }
}

int main(){
    void    *ptr;
    void    *wind;
    void    *im[5];
    int width = 10;
    int height = 10;
    int fd;
    void *sky;
    ptr = mlx_init();
    wind = mlx_new_window(ptr, 1600, 960, "so_long");
    if(!wind)
    {
        perror("Error");
        exit(1);
    }
    sky = mlx_xpm_file_to_image ( ptr, "./textures/sky.xpm", &width, &height);
    mlx_put_image_to_window(ptr, wind, sky, 0, 0);
    im[0] = mlx_xpm_file_to_image ( ptr, "./textures/grass2.xpm", &width, &height);
    im[1] = mlx_xpm_file_to_image ( ptr, "./textures/stone2.xpm", &width, &height);
    im[2] = mlx_xpm_file_to_image ( ptr, "./textures/ondia2.xpm", &width, &height);
    im[3] = mlx_xpm_file_to_image ( ptr, "./textures/potal2.xpm", &width, &height);
    im[4] = mlx_xpm_file_to_image ( ptr, "./textures/steve2.xpm", &width, &height); //steve
    clear_back(im[4]);
    fd = open("./maps/testmap.ber",O_RDONLY);
    map_set(im, fd, ptr, wind);
    
    //mlx_put_image_to_window(ptr, wind, im, 50, 50);
    mlx_loop(ptr);
}