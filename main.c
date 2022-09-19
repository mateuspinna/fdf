#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct  s_data 
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void    ft_vila(void *mlx, void *mlx_win, t_data img)
{
    int draw  = 150;
    
    mlx_put_image_to_window(mlx, mlx_win, img.img, 150, 100);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 450, 100);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 200, 150);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 400, 150);
   
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

}

int	close_win_x(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}


int	close_win(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;
    int     x;
    int     y;
	t_vars	vars;

    x = 0;
    y = 0;
    // INICIA A MILILIBX //
    mlx = mlx_init();
    
    // CRIA UMA JANELA DE TAMANHO DEFINIDO E NOMEIA ESSA JANELA //
    mlx_win = mlx_new_window(mlx, 650, 550, "Exterminadores de Bugs");

	vars.mlx = mlx;
	vars.win = mlx_win;

    // CRIA UMA NOVA IMAGEM QUE SERÁ JOGADA NA JANELA //
    img.img = mlx_new_image(mlx, 650, 550);
    
    // Get data atribuirá os valores de bpp, line lenght e endian adequados para aquela imagem //    
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
   
    // Nesta função um pixel é escrito na imagem na cordenada apontada por x e y. Esse loop fará com que um quadrado de 50 pixels seja escrito //
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
    
    // ESTA FUNÇÃO FARÁ COM QUE A IMAGEM ESCRITA SEJA JOGADA NA JANELA. NESTE CASO O DESENHO SERÁ O SIMBOLO DA MINHA VILA //
    ft_vila(mlx, mlx_win, img);    
    
	// HOOKANDO O ESC //
		
	mlx_hook(vars.win, 17, 0, close_win_x, &vars);
	mlx_hook(vars.win, 2, 0, close_win, &vars);
    // DEIXA A JANELA EM LOOP //

	mlx_loop(vars.mlx);

}
