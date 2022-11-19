#include "include/cub3d.h"
void square_drawing(t_cub *cub, int i, int j)
{
    int x;
    int y;
    y = i;
    while (y < 64)
    {
        x = j;
        while (x < 64)
        {
            // printf("adf\n");
            mlx_pixel_put(cub->mlx, cub->window,y ,x , 0xf0f0ffff / 16);
            x++;
        }
        y++;
    }
}

void paint_wall(t_cub *cub)
{
    int i, j;
    char *str1;
    str1 = mlx_xpm_file_to_image(cub->mlx, cub->file_so, &i, &j);
    char *str2;
    str2 = mlx_xpm_file_to_image(cub->mlx, cub->file_we, &i, &j);
    i = (cub->player.beg_y - 5) / 64;
    if (i < 0)
        i = 0;
    // j = 0;
   
    while (cub->map[i] && i < (cub->player.beg_y / 64) + 5)
    {
        j = (cub->player.beg_x / 64) - 5;
        if (j < 0)
            j = 0;
        while (cub->map[i][j] && j < (cub->player.beg_x / 64) + 5)
        {
            if (cub->map[i][j] == '1')
            {
                mlx_put_image_to_window(cub->mlx, cub->window, str2, j * 64, i * 64);
                // square_drawing(cub, i*64, j* 64);
                // exit(0);
            }
            else if (cub->map[i][j] == 'D')
            {
                mlx_put_image_to_window(cub->mlx, cub->window, str1, j * 64, i * 64);
            }
            j++;

        }
        i++;
    }
}
void player_drawing(t_cub *cub)
{
    int x;
    int y;
    y = cub->player.beg_y - 10;
    while (y < cub->player.beg_y + 10)
    {
        x = cub->player.beg_x - 10;
        while (x < cub->player.beg_x + 10)
        {
            // printf("adf\n");
            mlx_pixel_put(cub->mlx, cub->window, x, y, 0xf0f0ffff / 8);
            x++;
        }
        y++;
    }
}

void mini_map(t_cub *cub)
{
    paint_wall(cub);
    player_drawing(cub);
}