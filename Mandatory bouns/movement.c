#include "include/cub3d.h"
void number_d(t_cub *cub)
{
    int i;
    int k;
    int j;

    i = 0;
    k = 0;
    while (cub->map[i])
    {
        j = 0;
        while (cub->map[i][j])
        {
            if (cub->map[i][j] == 'D')
                cub->size_d++;
            j++;
        }
        i++;
    }
}
int check_arry(int *b, int x, t_cub *cub)
{
    int i;

    i = 0;
    while( i < cub->size_d)
    {
        if(b[i]== x)
            return 0;
        i++;
    }
    return 1;
}

int movement(int key, t_cub *cub)
{
//    number_d(cub);
//     cub->xx_D = ft_calloc(sizeof(int), cub->size_d + 1);
//     cub->yy_D = ft_calloc(sizeof(int), cub->size_d + 1);
    handling_keys(cub, key);
    ray_casting(cub);
    return 0;
}
