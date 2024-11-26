/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:10:48 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 14:55:58 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_angle(t_player *player, char dir)
{
	// ラジアンでは、１周は2π（2×3.14）
	// 北（270度）3π/2ラジアン
	if (dir == 'N')
		player->angle = (3 * PI) / 2;
	// 南（90度）π/2ラジアン
	else if (dir == 'S')
		player->angle = PI / 2;
	// 東（0度）0ラジアン
	else if (dir == 'E')
		player->angle = 0;
	// 西（180度）πラジアン
	else if (dir == 'W')
		player->angle = PI;
}

static void	set_player_position(t_player *player, int y, int x, char dir)
{
	// インデックスからマップのどの座標にいるか取得（PX：タイルのピクセル数）
	// タイルの幅 × 枚数 ＋ タイルの半分（中心）
	player->position.y = PX * y + (PX / 2);
	player->position.x = PX * x + (PX / 2);
	// どの方角を向いているかを三角比で設定
	// 半径1の円の中心にいる場合、北(0,-1)、南(0,1)、西(1,0)、東(-1,0)
	if (dir == 'N')
	{
		player->direction.y = -1;
		player->direction.x = 0;
	}
	else if (dir == 'S')
	{
		player->direction.y = 1;
		player->direction.x = 0;
	}
	else if (dir == 'E')
	{
		player->direction.y = 0;
		player->direction.x = 1;
	}
	else if (dir == 'W')
	{
		player->direction.y = 0;
		player->direction.x = -1;
	}
}

void	set_player_info(t_data *data, int y, int x, char **map)
{
	// map配列の座標を取得（探索用）
	data->player.array_pos.y = y;
	data->player.array_pos.x = x;
	// 画面上の座標と方角を取得（描画用）
	set_player_position(&data->player, y, x, map[y][x]);
	// 角度情報を持っておく
	set_player_angle(&data->player, map[y][x]);
}

void	check_player(t_data *data, char **map)
{
	int	y;
	int	x;
	int	player_found;

	y = 0;
	player_found = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// プレイヤーを見つけたらプレイヤー情報を取得
			if (ft_strchr("NSEW", map[y][x]))
			{
				// プレイヤーが複数人いたらエラー
				if (player_found)
					exit_error("Some players on map!", data);
				player_found = 1;
				set_player_info(data, y, x, map);
			}
			x++;
		}
		y++;
	}
	// プレイヤーが一人もいなかったらエラー
	if (!player_found)
		exit_error("No player on map!", data);
}
