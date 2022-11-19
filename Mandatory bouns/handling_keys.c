#include "include/cub3d.h"
void next_step_is_not_wall(t_cub *cub, double stepx, double stepy)
{
    if (cub->map[(int)(stepy) / 64][(int)(stepx) / 64] != '1' &&
        cub->map[(int)(stepy) / 64][(int)(stepx) / 64] != 'D')
    {
        cub->player.beg_x += stepx;
        cub->player.beg_y += stepy;
    }
}
int hasWallat(double x, double y, t_cub *cub, int key)
{
    if (x < 0 || x > cub->win_width || y < 0 || y > cub->win_height)
        return 1;
    int mapGrindIndexX = x / 64;
    int mapGrindIndexY = y / 64;
    if (cub->map[mapGrindIndexY][mapGrindIndexX] != '1')
    {
        if (key == UP_W || key == UP_A || key == UP_D)
        {

            if (cub->player.angle_of_player <= 2 * M_PI && cub->player.angle_of_player >= M_PI)
            {
                double IndexX = x;
                double IndexY = y - 10;
                int x = IndexX / 64;
                int y = IndexY / 64;
                if (cub->map[y][x] == '1')
                    return 1;
            }
            if (cub->player.angle_of_player < M_PI && cub->player.angle_of_player >= 0)
            {

                double IndexX;
                double IndexY;
                IndexX = x;
                IndexY = y + 10;
                int x = IndexX / 64;
                int y = IndexY / 64;
                if (cub->map[y][x] == '1')
                    return 1;
            }
            if (cub->player.angle_of_player >= M_PI_2 && cub->player.angle_of_player <= 1.5 * M_PI)
            {

                double IndexX = x - 10;
                double IndexY = y;
                int x = IndexX / 64;
                int y = IndexY / 64;

                if (cub->map[y][x] == '1')
                    return 1;
            }
            if (!(cub->player.angle_of_player > M_PI_2 && cub->player.angle_of_player < 1.5 * M_PI))
            {
                double IndexX;
                double IndexY;
                IndexX = x + 10;
                IndexY = y;
                int x = IndexX / 64;
                int y = IndexY / 64;
                if (cub->map[y][x] == '1')
                    return 1;
            }
        }
        if (key == DOWN_S)
        {

            if (cub->player.angle_of_player <= 2 * M_PI && cub->player.angle_of_player >= M_PI)
            {
                double IndexX = x;
                double IndexY = y + 10;
                int x = IndexX / 64;
                int y = IndexY / 64;
                if (cub->map[y][x] == '1')
                    return 1;
            }
            if (cub->player.angle_of_player < M_PI && cub->player.angle_of_player >= 0)
            {

                double IndexX;
                double IndexY;
                IndexX = x;
                IndexY = y - 10;
                int x = IndexX / 64;
                int y = IndexY / 64;
                if (cub->map[y][x] == '1')
                    return 1;
            }
            if (cub->player.angle_of_player >= M_PI_2 && cub->player.angle_of_player <= 1.5 * M_PI)
            {

                double IndexX = x + 10;
                double IndexY = y;
                int x = IndexX / 64;
                int y = IndexY / 64;

                if (cub->map[y][x] == '1')
                    return 1;
            }
            if (!(cub->player.angle_of_player > M_PI_2 && cub->player.angle_of_player < 1.5 * M_PI))
            {
                double IndexX;
                double IndexY;
                IndexX = x - 10;
                IndexY = y;
                int x = IndexX / 64;
                int y = IndexY / 64;
                if (cub->map[y][x] == '1')
                    return 1;
            }
        }
        if (cub->map[mapGrindIndexY][mapGrindIndexX] == 'D')
        {
            if (cub->D == 1)
                return 0;
            return 1;
        }
        return 0;
    }
    return (1);
}
int handling_keys(t_cub *cub, int key)
{
    double stepx = 0;
    double stepy = 0;
    int x = 0;
    int y = 0;
    double mapGrindIndexX ;
    double mapGrindIndexY;
     if (key == ESC)
        exit(ESC);
    if (key == 36)
    {
        int i = 0;
        if (cub->player.angle_of_player <= 2 * M_PI && cub->player.angle_of_player >= M_PI)
        {

             mapGrindIndexX = cub->player.beg_x;
             mapGrindIndexY = cub->player.beg_y - 64;
             x = mapGrindIndexX / 64;
             y = mapGrindIndexY / 64;
        }
        if (cub->player.angle_of_player < M_PI && cub->player.angle_of_player > 0)
        {
            mapGrindIndexX = cub->player.beg_x;
            mapGrindIndexY = cub->player.beg_y + 64;
             x = mapGrindIndexX / 64;
             y = mapGrindIndexY / 64;
        }
        if (cub->player.angle_of_player > M_PI_2 && cub->player.angle_of_player < 1.5 * M_PI)
        {

             mapGrindIndexX = cub->player.beg_x - 64;
             mapGrindIndexY = cub->player.beg_y;
             x = mapGrindIndexX / 64;
             y = mapGrindIndexY / 64;
           // up_to_fault(cub, x, y, i);
        }
        if (!(cub->player.angle_of_player > M_PI_2 && cub->player.angle_of_player < 1.5 * M_PI))
        {
            mapGrindIndexX = cub->player.beg_x + 64;
            mapGrindIndexY = cub->player.beg_y;
             x = mapGrindIndexX / 64;
             y = mapGrindIndexY / 64;
        }
        if (cub->k == cub->size_d)
            cub->k = 0;
        up_to_fault(cub, x, y, i);
    }

    // if (key == UP_W)
    // {
    //     stepx = 20 * cos(cub->player.angle_of_player);
    //     stepy = 20 * sin(cub->player.angle_of_player);
    // }
    // if (key == DOWN_S)
    // {
    //     stepx = -20 * cos(cub->player.angle_of_player);
    //     stepy = -20 * sin(cub->player.angle_of_player);
    // }
    // if (key == UP_A)
    // {
    //     stepx = 7 * cos(cub->player.angle_of_player - M_PI_2);
    //     stepy = 7 * sin(cub->player.angle_of_player - M_PI_2);
    // }
    // if (key == UP_D)
    // {
    //     stepx = -7 * cos(cub->player.angle_of_player   - M_PI_2);
    //     stepy = -7 * sin(cub->player.angle_of_player   - M_PI_2);
    // }
    // if (key == RIGHT)
    //     cub->player.angle_of_player += ROTAIONA_SPEED;
    // if (key == LEFT)
    // cub->player.angle_of_player -= ROTAIONA_SPEED;
    if (key == UP_W)
        cub->player.walkDirection = MOVE;
    if (key == DOWN_S)
        cub->player.walkDirection = -MOVE;
    if (key == UP_A)
        cub->player.walk_side_Direction = MOVE;
    if (key == UP_D)
        cub->player.walk_side_Direction = -MOVE;
    if (key == RIGHT)
        cub->player.angle_of_player += ROTAIONA_SPEED;
    if (key == LEFT)
        cub->player.angle_of_player -= ROTAIONA_SPEED;

    stepx = round(cub->player.beg_x + (cos(cub->player.angle_of_player) * cub->player.walkDirection + sin(cub->player.angle_of_player) * cub->player.walk_side_Direction));
    stepy = round(cub->player.beg_y + (sin(cub->player.angle_of_player) * cub->player.walkDirection - cos(cub->player.angle_of_player) * cub->player.walk_side_Direction));

    cub->player.angle_of_player = fix_angle(cub->player.angle_of_player);
    if (!hasWallat(stepx, stepy, cub, key))
    {
        cub->player.beg_x = stepx;
        cub->player.beg_y = stepy;
    }
    // next_step_is_not_wall(cub, stepx, stepy);
    return 0;
}
