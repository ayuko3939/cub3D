/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:00:44 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/24 21:38:47 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood_fill(t_data *data, char **map, int x, int y)
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
	// 4方向に探索を広げる
	if (flood_fill(data, map, x + 1, y) || flood_fill(data, map, x , y + 1)
	 || flood_fill(data, map, x - 1, y) || flood_fill(data, map, x , y - 1))
		return (EXIT_FAILURE);
	// 問題なければ正常終了
	return (EXIT_SUCCESS);
}

static void	check_map_structure(t_data *data, char **map)
{
	int	pos_x;
	int	pos_y;
	
	pos_x = (int)data->player.array_pos.x;
	pos_y = (int)data->player.array_pos.y;
	map[pos_y][pos_x] = '0';
	if (flood_fill(data, map, pos_x, pos_y))
		exit_error("Invalid map!", data);
}

static void check_components(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			// 無効な文字が含まれていないか確認
			if (!ft_strchr(" 01NSEW", map[i][j]))
				exit_error("Invalid characters on map!", data);
			j++;
		}
		i++;
	}
}

void	check_map(t_data *data)
{
	check_components(data, data->map);
	check_player(data, data->map);
	check_map_structure(data, data->map);
}
