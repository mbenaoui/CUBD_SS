#include "../include/cub3d.h"

void width_and_height_window(t_cub *cub)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (cub->map[i])
    {
        if (ft_strlen(cub->map[i]) >= j)
            j = ft_strlen(cub->map[i]);
        if (cub->map[i][0] == '\n')
            break;
        i++;
    }
    cub->win_width = j * 64;
    cub->win_height = i * 64;
}


void set_position(t_cub *cub, char c,int i ,int j)
{
    if(c == 'N')
        cub->player.angle_of_player = 3 * M_PI_2;
    else if(c == 'S')
        cub->player.angle_of_player = M_PI_2;
    else if(c == 'E')
        cub->player.angle_of_player = 0;
    else if(c == 'W')
        cub->player.angle_of_player = M_PI;
    cub->player.beg_x = j*64;
    cub->player.beg_y = i*64;
}

void position_of_player(t_cub *cub)
{
    int i;
    int j;

    i = 0;
    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            if (cub->map[i][j] == 'N')
                set_position(cub, 'N', i ,j);
            else if (cub->map[i][j] == 'S')
                set_position(cub, 'S', i ,j);
            else if (cub->map[i][j] == 'E')
                set_position(cub, 'E', i ,j);
            else if (cub->map[i][j] == 'W')
                set_position(cub, 'W', i ,j);
            j++;
        }
        i++;
    }
}