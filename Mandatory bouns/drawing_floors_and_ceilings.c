#include "include/cub3d.h"


void drawing_floors(t_cub *cub, int color)
{
    int i = cub->win_height / 2;
    int j;
    while (i < cub->win_height)
    {
        j = 0;
        while (j < cub->win_width)
        {
            cub->data_image[i * cub->win_width + j] = color;
            j++;
        }
        i++;
    }
}


void drawing_ceilings(t_cub *cub, int color)
{
    int i = 0;
    int j;
    while (i < cub->win_height / 2)
    {
        j = 0;
        while (j < cub->win_width)
        {
            cub->data_image[i * cub->win_width + j] = color;
            j++;
        }
        i++;
    }
}
