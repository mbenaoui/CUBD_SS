#include "include/cub3d.h"
void draw_line(t_cub *cub, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX = endX - beginX;                            // 10
    double deltaY = endY - beginY;                            // 5
    int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY)); // 11.1
    deltaX /= pixels;                                         // 0
    deltaY /= pixels;                                         // 0
    double pixelX = beginX;                                   // 10
    double pixelY = beginY;                                   // 5
    while (pixels)
    {
        mlx_pixel_put(cub->mlx, cub->window, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        --pixels;
    }
}
void directions_playing(double angle, t_cub *cub)
{
    cub->player.lefte = 0;
    cub->player.right = 0;
    cub->player.down = 0;
    cub->player.up = 0;

    if (angle <= 3 * M_PI_2 && angle >= M_PI_2)
        cub->player.lefte = 1;
    else
        cub->player.right = 1;
    if (angle > 0 && angle < M_PI)
        cub->player.down = 1;
    else
        cub->player.up = 1;
}
void search_for_first_step_vert(t_cub *cub, double *stepx, double *stepy)
{
    directions_playing(cub->player.ry_angle, cub);
    *stepx = (cub->player.beg_x - (int)(cub->player.beg_x / 64) * 64);
    if (cub->player.right == 1)
        *stepx = 64 - *stepx;
    if (cub->player.lefte == 1)
        *stepx *= -1;
    *stepy = *stepx * tan(cub->player.ry_angle);
}

void search_for_first_step_hor(t_cub *cub, double *stepx, double *stepy)
{
    directions_playing(cub->player.ry_angle, cub);
    *stepy = (cub->player.beg_y - (int)(cub->player.beg_y / 64) * 64);
    if (cub->player.down == 1)
        *stepy = 64 - *stepy;
    if (cub->player.up == 1)
        *stepy *= -1;
    *stepx = *stepy / tan(cub->player.ry_angle);
}

void search_for_first_step(t_cub *cub, double *stepx, double *stepy)
{
    double her_stepx;
    double her_stepy;
    double ver_stepx;
    double ver_stepy;

    search_for_first_step_vert(cub, &ver_stepx, &ver_stepy);
    search_for_first_step_hor(cub, &her_stepx, &her_stepy);
    if (sqrt(pow(ver_stepx, 2) + pow(ver_stepy, 2)) < sqrt(pow(her_stepx, 2) + pow(her_stepy, 2)))
    {
        *stepx = ver_stepx;
        *stepy = ver_stepy;
    }
    else
    {
        *stepx = her_stepx;
        *stepy = her_stepy;
    }
}

void search_for_delta_step_vert(t_cub *cub, double *ver_deltx, double *ver_delty)
{
    directions_playing(cub->player.ry_angle, cub);
    (*ver_deltx) = 64;
    if (cub->player.lefte)
        (*ver_deltx) *= -1;
    (*ver_delty) = (*ver_deltx) * tan(cub->player.ry_angle);
}

void search_for_delta_step_hor(t_cub *cub, double *hor_deltx, double *hor_delty)
{
    directions_playing(cub->player.ry_angle, cub);
    (*hor_delty) = 64;
    if (cub->player.up)
        (*hor_delty) *= -1;
    (*hor_deltx) = (*hor_delty) / tan(cub->player.ry_angle);
}

void search_for_wall_ver(t_cub *cub, double *stepx, double *stepy)
{
    double ver_deltx;
    double ver_delty;
    double i;
    double j;
    search_for_first_step_vert(cub, stepx, stepy);
    if (cub->player.lefte)
        (*stepx)--;
    search_for_delta_step_vert(cub, &ver_deltx, &ver_delty);
    (*stepx) += cub->player.beg_x;
    (*stepy) += cub->player.beg_y;
    cub->if_ver = 0;
    i = (*stepx);
    j = (*stepy);
    while ((i) > 0 && (i) < cub->win_width && (j) > 0 && (j) < cub->win_height)
    {
        if (cub->map[(int)(j / 64)][(int)(i / 64)] == '1' || (cub->map[((int)(j / 64))][(((int)(i / 64)))] == 'D'))
        {
            cub->if_ver = 1;
            (*stepx) = i;
            (*stepy) = j--;
            break;
        }
        i += ver_deltx;
        j += ver_delty;
    }
}

void search_for_wall_hor(t_cub *cub, double *stepx, double *stepy)
{
    double ver_deltx;
    double ver_delty;
    double i;
    double j;

    search_for_first_step_hor(cub, stepx, stepy);
    search_for_delta_step_hor(cub, &ver_deltx, &ver_delty);
    (*stepx) += cub->player.beg_x;
    (*stepy) += cub->player.beg_y;
    i = (*stepx);
    j = (*stepy);
    cub->if_hor = 0;
    if (cub->player.up == 1)
        j--;
    while (i > 0 && i < cub->win_width && j > 0 && j < cub->win_height)
    {
        if (cub->map[((int)(j / 64))][(((int)(i / 64)))] == '1' || (cub->map[((int)(j / 64))][(((int)(i / 64)))] == 'D'))
        {
            cub->if_hor = 1;
            *stepx = i;
            *stepy = j;
            break;
        }
        i += ver_deltx;
        j += ver_delty;
    }
}

void intersection_with_ver_or_hor_wall(t_cub *cub, double *Wallx, double *Wally)
{
    t_var v;

    cub->player.ry_angle = fix_angle(cub->player.ry_angle);
    search_for_wall_ver(cub, &v.wall_ver_x, &v.wall_ver_y);
    search_for_wall_hor(cub, &v.wall_hor_x, &v.wall_hor_y);
    if (cub->if_ver)
        v.a = sqrt(pow((cub->player.beg_x - v.wall_ver_x), 2) +
                   pow((cub->player.beg_y - v.wall_ver_y), 2));
    else
        v.a = MAX_INT;
    if (cub->if_hor)
        v.b = sqrt(pow(cub->player.beg_x - v.wall_hor_x, 2) +
                   pow(cub->player.beg_y - v.wall_hor_y, 2));
    else
        v.b = MAX_INT;
    if (v.a < v.b)
    {
        cub->distanc_if_v_or_h = 1;
        *Wallx = v.wall_ver_x;
        *Wally = v.wall_ver_y;
    }
    else
    {
        cub->distanc_if_v_or_h = 0;
        *Wallx = v.wall_hor_x;
        *Wally = v.wall_hor_y;
    }
}

void drawing_walls(t_cub *cub, t_var *v)
{
    int textur_ofs_X;
    int textur_ofs_Y;
    if (cub->distanc_if_v_or_h)
        textur_ofs_X = (int)v->Wally % 64;
    else
        textur_ofs_X = (int)v->Wallx % 64;
    for (int y = v->start_y; y < v->end_y; y++)
    {
        int color;
        int distancfromtop = y + (v->walstrph / 2) - (cub->win_height / 2);
        textur_ofs_Y = distancfromtop * ((double)64 / v->walstrph);
        if (cub->map[((int)(v->Wally / 64))][(((int)(v->Wallx / 64)))] == 'D')
            color = cub->txts->data_txt_dor_open[(64 * textur_ofs_Y) + textur_ofs_X];
        else
        {

            if (cub->distanc_if_v_or_h)
            {
                if (cub->player.right)
                    color = cub->txts->data_txt_ea[(64 * textur_ofs_Y) + textur_ofs_X];
                else
                    color = cub->txts->data_txt_we[(64 * textur_ofs_Y) + textur_ofs_X];
            }
            else
            {
                if (cub->player.up)
                    color = cub->txts->data_txt_no[(64 * textur_ofs_Y) + textur_ofs_X];
                else
                    color = cub->txts->data_txt_so[(64 * textur_ofs_Y) + textur_ofs_X];
            }
        }
        // cub->data_image[(cub->win_width * y) + v->i] = color;
        cub->data_image[(cub->win_width * y) + v->i] = color;
    }
}

int ray_casting(t_cub *cub)
{
    t_var v;

    v.i = -1;
    int arr[3];
   // printf("{%f}\n",cub->player.angle_of_player);
    mlx_clear_window(cub->mlx, cub->window);
    cub->image = mlx_new_image(cub->mlx, cub->win_width, cub->win_height);
    cub->data_image = (int *)mlx_get_data_addr(cub->image, &(arr[0]), &(arr[1]), &(arr[2]));
    cub->player.ry_angle = cub->player.angle_of_player - 30 * (M_PI / 180);

    drawing_floors(cub, 0x00ff0ff00 / 3);
    drawing_ceilings(cub, 0x00ff0ff00 / 6);
    while (++v.i < cub->win_width)
    {
        intersection_with_ver_or_hor_wall(cub, &v.Wallx, &v.Wally);
        // draw_line(cub, cub->player.beg_x, cub->player.beg_y, v.Wallx, v.Wally, 0x00ff0ff00 / 4);
        // mlx_pixel_put(cub->mlx,cub->window ,v.Wallx - cub->player.beg_x , v.Wally - cub->player.beg_x, 0x00ff0ff00 / 4);
        v.raydst = sqrt(pow((cub->player.beg_x - v.Wallx), 2) + pow((cub->player.beg_y - v.Wally), 2));
        v.distprojPlan = (cub->win_width / 2) / tan(FOV / 2);
        v.teta = cub->player.ry_angle - cub->player.angle_of_player;
        v.corr_dst = v.raydst * cos(v.teta);
        v.walstrph = (64 / v.corr_dst) * v.distprojPlan;
        v.start_y = (cub->win_height / 2) - (v.walstrph / 2);
        if (v.start_y < 0)
            v.start_y = 0;
        v.end_y = (cub->win_height / 2) + (v.walstrph / 2);
        if (v.end_y > cub->win_height)
            v.end_y = cub->win_height;
        drawing_walls(cub, &v);
        cub->player.ry_angle += (60 * (M_PI / 180)) / cub->win_width;
    }
    mlx_put_image_to_window(cub->mlx, cub->window, cub->image, 0, 0);
    mini_map(cub);
    return 0;
}
