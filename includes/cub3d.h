/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:06:08 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 16:57:17 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h> // open
# include <math.h>
# include <stdbool.h> // libftで使う場合はこっちから消す
# include <stdio.h>

// MESSAGE　COLOR PARETTO
# define RED "\033[38;5;196;1m"
# define YELLOW "\033[38;5;226;1m"
# define INDIGO "\033[38;5;025;1m"
# define VIOLET "\033[38;5;062;1m"
# define END "\033[0m"

// MINIMAP COLOR PARETTO
# define BLACK 0x00000000
# define LIGHT_GREY 0x00dfdfdf
# define NAVY 0x00233B6C
# define ORANGE 0x00ee7800

// KEYBOARD CODES
# define ESC 65307 // ESCキー番号
# define W 119     // Wキー番号
# define S 115     // Sキー番号
# define A 97      // Aキー番号
# define D 100     // Dキー番号
# define LA 65361  // 左矢印キー番号
# define RA 65363  // 右矢印キー番号
# define M 109     // Mキー番号（ミニマップ表示切替用）

// SIZE
# define PX 64              // 各タイルのピクセル数
# define PACE 10            // プレイヤーの移動ペース
# define TURNANGLE 0.1      // プレイヤーの回転角度
# define PLYLEN 9           // プレイヤーの描画サイズ
# define FOV 1.047198       // 視野角（Field of View）60°
# define HALF_FOV 0.523599  // 視野角の半分 30°
# define PLANE_DIST 652.719 // 平面の投影距離
# define WIDTH 680          // ウィンドウの幅
# define HEIGHT 480         // ウィンドウの高さ

# define PI 3.14159265      // 円周率（ラジアン計算用）
# define TOLERANCE 0.000001 // 計算誤差の許容値
# define X 0                // X方向のインデックス
# define Y 1                // Y方向のインデックス

# define CHECKED 'V' // flood_fill用　チェック済みの印

enum		e_direction
{
	NORTH,	// 北
	SOUTH,	// 南
	WEST,	// 西
	EAST,	// 東
	NONE	// なし
};

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_vct_int
{
	int			x;
	int			y;
}				t_vct_int;

typedef struct s_player
{
	t_vector	position;	// 現在位置 (x, y座標)
	t_vct_int	array_pos;	// 現在位置 (x, y座標) map配列の探索用にintの値を格納
	t_vector	direction;	// 向きベクトル (x, y座標)
	double		angle;		// 向きの角度 (ラジアン単位)
}				t_player;

typedef struct s_ray
{
	t_vector	vct;			// 現在のY座標
	t_vector	next_grid;		// 次のグリッドラインまでの距離
	t_vector	direction;		// レイの進行方向ベクトル
	double		angle;			// レイの角度（ラジアン）
	double		distance;		// 壁に当たるまでの距離
	int			hit_wall;		// 垂直な壁に衝突したかを示すフラグ（1: 垂直、0: 水平）
	int			wall_dir;		// 衝突した壁のテクスチャID(e_direction)
	double		wall_hit_point; // 衝突した壁の位置（テクスチャ座標の計算に使用）
	int			wall_height;	// レイの結果として計算された壁の高さ
}				t_ray;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_texture
{
	t_image		image;
	int			width;
	int			height;
}				t_texture;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_image		image;
}				t_window;

typedef struct s_data
{
	char		**file;				//.cubファイルの中身
	char		*texture_paths[5];	// テクスチャファイルパス 5つ目はNULL
	int			floor_rgb[3];		// 床の色（RGB）
	int			ceiling_rgb[3];		// 天井の色（RGB）
	char		**map;				// マップデータ（2D配列）
	int			rows;				// マップの行数
	int			columns;			// マップの列数
	t_player	player;				// プレイヤー情報
	t_window	graphic;			// mlx関連（ウィンドウ、イメージ）
	t_texture	textures[5];		// mlx関連（テクスチャ）
	t_ray		*rays;				// mlx関連（レイキャスティング）
	bool		show_minimap;		// ミニマップ表示フラグ
	int			minimap_scale;		// ミニマップのスケール
}				t_data;

void		check_map(t_data *data);
void		set_player_info(t_data *data, int y, int x, char **map);
void		check_player(t_data *data, char **map);
double		next_grid_distance_y(int y, double angle);
double		next_grid_distance_x(int x, double angle);
double		get_y_step(int opose, double angle);
double		get_x_step(int adj, double angle);
void		increment_ray_length(t_ray *ray, double step_y, double step_x);
void		draw_walls(t_data *data, t_ray *rays);
void		draw_floor_and_ceiling(t_data *data);
void		image_pixel_put(t_image *img, int x, int y, int color);
int			get_texture_color(t_data *data, int y, int offset_x, t_ray ray);
void		draw_minimap(t_data *data, t_window *graphic);
int			key_press(int key, t_data *data);
void		error_print(char *message);
void		exit_error(char *message, t_data *data);
void		exit_game(t_data *data);
void		set_data_from_file(t_data *data, char **file);
void		init_data(t_data *data, char *filepath);
int			get_map_columns(char **file);
int			get_map_rows(char **file);
void		set_map(t_data *data, char **file);
void		set_metadata(t_data *data, char ***file);
void		init_mlx(t_data *data);
int			validate(int ac, char **av);
int			main(int ac, char **av);
int			check_wall(int pos_y, int pos_x, char **map);
void		move_player(t_player *p, double dir_y, double dir_x, char **map);
void		raycasting(t_data *data, t_ray *rays);
void		rendering(t_data *data);
void		free_all(char **array);
bool		is_include_char(char *s, int c);
void		replace_str(char *str, char *remove, char replace);
int			strarr_size(char **arr);
bool		is_str_type(char *str, int (*function)(int));
void		setup(t_data *data);

// debug
// void	print_map(t_data *data);
// void	print_info(t_data *data);

#endif