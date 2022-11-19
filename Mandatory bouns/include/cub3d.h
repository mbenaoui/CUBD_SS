#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "mlx.h"
#include <math.h>
#include <limits.h>

#define FOV 1.0472
#define INC_FOV 0.0174533333
#define UP_W 13
#define DOWN_S 1
#define UP_A 0
#define UP_D 2
#define LEFT 123
#define RIGHT 124
#define MOVE 20
#define WIN_W 320;
#define WIN_H 670;
#define ESC 53
#define MAX_INT 2147483647
#define ROTAIONA_SPEED 5 * (M_PI / 180)

typedef struct t_var
{
    double wall_ver_x;
    double wall_ver_y;
    double wall_hor_x;
    double wall_hor_y;
    double a;
    double b;
    int i;
    int j;
    int k;
    int len;
    int x;
    int y;
    char *str;
    char *dst;
    char **tab;
    double distprojPlan;
    double teta;
    double corr_dst;
    double raydst;
    int walstrph;
    int start_y;
    int end_y;
    double Wallx;
    double Wally;
} t_var;

typedef struct s_color
{
    int _r;
    int _g;
    int _b;
} t_color;

typedef struct s_player
{
    int lefte;
    int right;
    int up;
    int down;
    int beg_x;
    int beg_y;
    int end_x;
    int end_y;
    double angle_of_player;
    double rotaionaSpeed;
    int walkDirection;
    int walk_side_Direction;
    double ry_angle;
    int x_D;
    int y_D;
} t_player;
typedef struct s_textures
{
    void *txt_so;
    void *txt_no;
    void *txt_we;
    void *txt_ea;
    int *data_txt_so;
    int *data_txt_no;
    int *data_txt_we;
    int *data_txt_ea;
    int *data_txt_dor;
    int *data_txt_dor_open;
} t_textures;

typedef struct s_cub3d
{

    char **map;
    int *xx_D;
    int *yy_D;
    int k;
    int size_d;
    char **lines;
    char *file_so;
    char *file_no;
    char *file_we;
    char *file_ea;
    char *before_map;
    int size1;
    int size2;
    t_color *rgb_f;
    t_color *rgb_c;
    t_player player;
    char *mlx;
    int win_height;
    int win_width;
    char *window;
    int moveSpeed;
    double move_hor;
    double move_vert;
    int if_hor;
    int if_ver;
    int distanc_if_v_or_h;
    void *image;
    int *data_image;
    int D;
    t_textures *txts;
} t_cub;

int main(int argc, char **argv);
// parsing
void check_map_valid(t_cub *cub, char *path);
int ft_strcmp(char *s1, char *s2);
void msg_error(int status);
int size_map(char *path);
void free_tab(char **tab);
int handling_texture(t_cub *cub, int i, int j);
void search_color(t_cub *cub, char *str, int *j, int index);
void handling_color(t_cub *cub, char *des, int index, int i);
void check_color(t_var var);
int len_tab(char **tab, int index);
int handling_texture(t_cub *cub, int i, int j);
void handling_texture_2(char **str, int *j, t_cub *cub, int i);
void print_info(char *str, int n);
void check_may_map(char **map, int i, int j, int k);
int if_player(char c);

//
void position_of_player(t_cub *cub);
void width_and_height_window(t_cub *cub);
void number_d(t_cub *cub);
int check_arry(int *b, int x, t_cub *cub);
void up_to_fault(t_cub *cub, int x, int y, int i);
void draw_line(t_cub *cub, int beginX, int beginY, int endX, int endY, int color);
void white_window(t_cub *cub);
void paint_wall(t_cub *cub);
void init_textures(t_cub *cub);
int movement(int key, t_cub *cub);
void ft_init_mlx(t_cub *cub);
t_cub *int_cub();
int handling_keys(t_cub *cub, int key);
int ray_casting(t_cub *cub);
double fix_angle(double angle);
void paint_wall(t_cub *cub);
void mini_map(t_cub *cub);
int move(int key, t_cub *cub);
void drawing_floors(t_cub *cub, int color);
void drawing_ceilings(t_cub *cub, int color);
#endif