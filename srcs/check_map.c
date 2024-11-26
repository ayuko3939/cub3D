/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:00:44 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 15:51:47 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood_fill(t_data *data, char **map, int y, int x)
{
	// インデックスがマップの範囲外ならエラー
	if (x < 0 || x >= data->columns || y < 0 || y >= data->rows)
		return (EXIT_FAILURE);
	// 対象がスペースならエラー
	if (map[y][x] == ' ')
		return (EXIT_FAILURE);
	// 対象が壁かチェック済みなら探索終了
	if (map[y][x] == '1' || map[y][x] == CHECKED)
		return (EXIT_SUCCESS);
	// 問題なければ今の位置をチェック済みにする
	map[y][x] = CHECKED;

	// print_map(data); // test

	// 4方向に探索を広げる
	if (flood_fill(data, map, y, x + 1) || flood_fill(data, map, y + 1, x)
	 || flood_fill(data, map, y, x - 1) || flood_fill(data, map, y - 1, x))
		return (EXIT_FAILURE);
	// 問題なければ正常終了
	return (EXIT_SUCCESS);
}

static void	check_map_structure(t_data *data, char **map)
{
	int		x;
	int		y;
	char	org;
	
	// 扱いやすいように代入
	x = data->player.array_pos.x;
	y = data->player.array_pos.y;
	// "NSEW"を保存しておく
	org = map[y][x];
	// 探索対象にするため'0'にしておく
	map[y][x] = '0';
	// 探索開始
	if (flood_fill(data, map, y, x))
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

static void check_components(t_data *data, char **map)
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
