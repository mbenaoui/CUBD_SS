#include "include/cub3d.h"

t_cub *int_cub()
{
    t_cub *cub;
    cub = ft_calloc(sizeof(t_cub), 1);
    cub->rgb_c = ft_calloc(sizeof(t_color), 1);
    cub->rgb_f = ft_calloc(sizeof(t_color), 1);
    cub->txts = ft_calloc(sizeof(t_textures), 1);
    return cub;
}

void ft_init_mlx(t_cub *cub)
{
    int arr[3];
    width_and_height_window(cub);
    position_of_player(cub);
    cub->mlx = mlx_init();
    cub->window = mlx_new_window(cub->mlx, cub->win_width, cub->win_height, "cub3d");
    // cub->image = mlx_new_image(cub->mlx, cub->win_width, cub->win_height);
    init_textures(cub);
}
