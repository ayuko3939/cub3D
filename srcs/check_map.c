/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:00:44 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:49:15 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood_fill(t_data *data, int y, int x, t_vct_int *dir)
{
	int			i;

	// インデックスがマップの範囲外ならエラー
	if (x < 0 || x >= data->columns || y < 0 || y >= data->rows)
		return (EXIT_FAILURE);
	// 対象がスペースならエラー
	if (data->map[y][x] == ' ')
		return (EXIT_FAILURE);
	// 対象が壁かチェック済みなら探索終了
	if (data->map[y][x] == '1' || data->map[y][x] == CHECKED)
		return (EXIT_SUCCESS);
	// 問題なければ今の位置をチェック済みにする
	data->map[y][x] = CHECKED;
	// 8方向を再帰的にチェック
	i = 0;
	while (i < 8)
	{
		if (flood_fill(data, y + dir[i].y, x + dir[i].x, dir))
			return (EXIT_FAILURE);
		i++;
	}
	// 問題なければ正常終了
	return (EXIT_SUCCESS);
}

static void	set_directions(t_vct_int *directions)
{
	directions[0] = (t_vct_int){-1, -1}; // 左上
	directions[1] = (t_vct_int){-1, 0}; // 上
	directions[2] = (t_vct_int){-1, 1}; // 右上
	directions[3] = (t_vct_int){0, -1}; // 左
	directions[4] = (t_vct_int){0, 1}; // 右
	directions[5] = (t_vct_int){1, -1}; // 左下
	directions[6] = (t_vct_int){1, 0}; // 下
	directions[7] = (t_vct_int){1, 1}; // 右下
}

static void	check_map_structure(t_data *data, char **map)
{
	int			x;
	int			y;
	char		org;
	t_vct_int	dir[8];

	// 扱いやすいように代入
	x = data->player.array_pos.x;
	y = data->player.array_pos.y;
	// "NSEW"を保存しておく
	org = map[y][x];
	// 探索対象にするため'0'にしておく
	map[y][x] = '0';
	// 探索方向を初期化
	set_directions(dir);
	// 探索開始
	if (flood_fill(data, y, x, dir))
		exit_error("Invalid map!", data);
	// マップを復元する
	map[y][x] = org;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == CHECKED)
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

static void	check_components(t_data *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// 無効な文字が含まれていないか確認
			if (!ft_strchr(" 01NSEW", map[y][x]))
				exit_error("Invalid characters on map!", data);
			x++;
		}
		y++;
	}
}

void	check_map(t_data *data)
{
	check_components(data, data->map);
	check_player(data, data->map);
	check_map_structure(data, data->map);
}
