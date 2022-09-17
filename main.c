#include "mlx/mlx.h"

typedef struct  s_data 
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x;
    int     y;


    x = 0;
    y = 0;
    // INICIA A MILILIBX //
    mlx = mlx_init();
    
    // CRIA UMA JANELA DE TAMANHO DEFINIDO E NOMEIA ESSA JANELA //
    mlx_win = mlx_new_window(mlx, 650, 550, "Hello world!");
    
    img.img = mlx_new_image(mlx, 650, 550);
    
       
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
   
    while (x <= 50)
    {
        y = 0;
        while (y <= 50)
        {
            my_mlx_pixel_put(&img, x, y, 0x00ff0000);
            y++;
        }
        x++;
    }

    mlx_put_image_to_window(mlx, mlx_win, img.img, 150, 100);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 450, 100);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 200, 150);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 400, 150);
   
    int draw  = 150;
    while (draw <= 450)
    {
        mlx_put_image_to_window(mlx, mlx_win, img.img, draw, 200);
        draw += 50;
    }
    draw = 100;
    while (draw <= 500)
    {
        if (!(draw == 200) && !(draw == 400))    
            mlx_put_image_to_window(mlx, mlx_win, img.img, draw, 250);
        draw += 50;
    }
    draw = 50;
    while (draw <= 550)
    {
        mlx_put_image_to_window(mlx, mlx_win, img.img, draw, 300);
        draw += 50;
    }
    draw = 50;
    while (draw <= 550)
    {
        if (!(draw == 100) && !(draw == 500))    
            mlx_put_image_to_window(mlx, mlx_win, img.img, draw, 350);
        draw += 50;
    }
    draw = 50;
    while (draw <= 550)
    {
        if (!(draw == 100) && !(draw == 500) && !(draw >= 200 && draw< 450))    
            mlx_put_image_to_window(mlx, mlx_win, img.img, draw, 400);
        draw += 50;
    }
    draw = 200;
    while (draw <= 450)
    {
        if ((draw >= 200 && draw < 300) || (draw >= 350 && draw < 450))    
            mlx_put_image_to_window(mlx, mlx_win, img.img, draw, 450);
        draw += 50;
    }

    
    
    // DEIXA A JANELA EM LOOP //
     mlx_loop(mlx);

}
