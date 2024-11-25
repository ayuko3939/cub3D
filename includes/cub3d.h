/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:06:08 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/24 22:17:16 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>   // open
# include <stdbool.h> // libftで使う場合はこっちから消す
# include <stdio.h>
# include <stdlib.h> // exit libftで使う場合はこっちから消す

// Color Paretto
# define RED "\033[38;5;196;1m"
# define ORANGE "\033[38;5;208;1m"
# define YELLOW "\033[38;5;226;1m"
# define GREEN "\033[38;5;082;1m"
# define BLUE "\033[38;5;027;1m"
# define INDIGO "\033[38;5;093;1m"
# define VIOLET "\033[38;5;163;1m"
# define WHITE "\033[38;5;231;1m"
# define BROWN "\033[38;5;137;1m"
# define END "\033[0m"

// SIZE
# define PX 64              // 各タイルのピクセル数
# define PACE 10            // プレイヤーの移動ペース
# define TURNANGLE 0.1      // プレイヤーの回転角度
# define PLYLEN 9           // プレイヤーの描画サイズ
# define FOV 1.047198       // 視野角（Field of View）
# define HALF_FOV 0.523599  // 視野角の半分
# define PLANE_DIST 652.719 // 平面の投影距離
# define WIDTH 680   // ウィンドウの幅
# define HEIGHT 480  // ウィンドウの高さ

# define PI 3.14159265 // 円周率（ラジアン計算用）

# define CHECKED 'V' // flood_fill用　チェック済みの印

enum		e_direction
{
	UNDEFINED = -1, // 未設定
	NORTH,          // 北
	SOUTH,          // 南
	WEST,           // 西
	EAST,           // 東
	NONE            // なし
};

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct s_player
{
	t_vector position;  // 現在位置 (x, y座標)
	t_vector array_pos; // 現在位置 (x, y座標) map配列の探索用にintの値を格納
	t_vector direction; // 向きベクトル (x, y座標)
	double angle;       // 向きの角度 (ラジアン単位)
}			t_player;

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
	char		**file;            //.cubファイルの中身
	char		*texture_paths[5]; // テクスチャファイルパス 5つ目はNULL
	int			floor_rgb[3];       // 床の色（RGB）
	int			ceiling_rgb[3];     // 天井の色（RGB）
	char		**map;             // マップデータ（2D配列）
	int			rows;               // マップの行数
	int			columns;            // マップの列数
	t_player 	player;        		// プレイヤー情報
	t_window	graphic;			// mlx関連（ウィンドウ、イメージ）
}			t_data;

void		error_print(char *message);
void		exit_error(char *message, t_data *data);

void		free_all(char **array);
bool		is_include_char(char *s, int c);
void		replace_str(char *str, char *remove, char replace);
int			strarr_size(char **arr);
bool		is_str_type(char *str, int (*function)(int));

void		set_metadata(t_data *data, char ***file);
int			get_map_columns(char **file);
int			get_map_rows(char **file);
void		set_map(t_data *data, char **file);
void		init_data(t_data *data, char *filepath);

void		check_player(t_data *data, char **map);
void		check_map(t_data *data);

#endif