#include "include/cub3d.h"
int move_t(int key, t_cub *cub)
{

    if (key == UP_W)
        cub->player.walkDirection = 0;
    if (key == DOWN_S)
        cub->player.walkDirection = 0;
    if (key == UP_A)
        cub->player.walk_side_Direction = 0;
    if (key == UP_D)
        cub->player.walk_side_Direction = 0;
    // if (key == RIGHT_ARR)
    //     cub->player.rotaionagngle += cub->player.rotaionaSpeed;
    // if (key == LEFT_ARR)
    //     cub->player.rotaionagngle -= cub->player.rotaionaSpeed;
    return 0;
}
int mouse_move(int x, int y, t_cub *cub)
{
    
    static int view;
    (void)y;
    if( x < cub->win_width && x > 0 && y < cub->win_height && y > 0)
    {

    if (view != x && view > x)
        cub->player.angle_of_player += ROTAIONA_SPEED;
    else
        cub->player.angle_of_player -= ROTAIONA_SPEED;
    }
    view = x + 1;
    // printf("%f\n", cub->player.ry_angle);
    movement(-1, cub);
    return 0;
}

int main(int agrc, char **argv)
{
    if (agrc != 2)
        return 1;
    t_cub *cub;
    cub = int_cub();
    cub->k = 0;
    check_map_valid(cub, argv[1]);
    ft_init_mlx(cub);
    number_d(cub);
    cub->xx_D = ft_calloc(sizeof(int), cub->size_d + 1);
    cub->yy_D = ft_calloc(sizeof(int), cub->size_d + 1);
    // paint_wall(cub);
    // ray_casting(cub);
    mlx_hook(cub->window, 2, 1L, movement, cub);
    mlx_hook(cub->window, 6, 1L << 0, mouse_move, cub);
    // mlx_loop_hook(cub->mlx, ray_casting, cub);
    mlx_hook(cub->window, 3, 1L << 1, move_t, cub);
    mlx_loop(cub->mlx);
    free_tab(cub->lines);
    return 0;
}

// printf("%d | %d  | %f\n", cub->player.beg_x, cub->player.beg_y, cub->player.angle_of_player);