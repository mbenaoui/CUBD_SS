#include "include/cub3d.h"
void up_to_fault(t_cub *cub, int x, int y, int i)
{
    if (cub->map[y][x] == 'D')
    {
        cub->map[y][x] = '0';
        if (check_arry(cub->xx_D, x, cub) || check_arry(cub->yy_D, y, cub))
        {
            cub->xx_D[cub->k] = x;
            cub->yy_D[cub->k] = y;
            cub->k++;
        }
    }
    else if (cub->map[y][x] == '0')
    {
        i = 0;
        while (i <= cub->size_d)
        {
            if (cub->map[cub->yy_D[i]][cub->xx_D[i]] == '0')
                if (x == cub->xx_D[i] && y == cub->yy_D[i])
                {
                    cub->map[cub->yy_D[i]][cub->xx_D[i]] = 'D';
                    break;
                }
            i++;
        }
    }
}