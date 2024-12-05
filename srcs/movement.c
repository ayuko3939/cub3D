/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:30:11 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:39:32 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// (0)none  (1)wall
int	check_wall(int pos_y, int pos_x, char **map)
{
	int	x;
	int	y;

	// 座標をマップのグリッド位置に変換
	y = pos_y / PX;
	x = pos_x / PX;
	// 移動先の座標が壁(1)なら戻り値(1)、壁でなければ(0)
	if (map[y][x] == '1')
		return (1);
	return (0);
}

// (true)player hits wall  (false)player can move 
static bool	check_hit_wall(int pos_y, int poy_x, char **map)
{
	// 移動予定先（体の中心、体の幅（前後左右）が壁に当たらないかを確認して、どれか1つでも当たれば1を返す）
	return (check_wall(pos_y, poy_x, map)
		|| check_wall(pos_y - (PLYLEN / 2), poy_x - (PLYLEN / 2), map)
		|| check_wall(pos_y - (PLYLEN / 2), poy_x + (PLYLEN / 2), map)
		|| check_wall(pos_y + (PLYLEN / 2), poy_x - (PLYLEN / 2), map)
		|| check_wall(pos_y + (PLYLEN / 2), poy_x + (PLYLEN / 2), map));
}

void	move_player(t_player *p, double dir_y, double dir_x, char **map)
{
	// 移動予定先が壁じゃなければ、現在地を更新する
	if (!check_hit_wall(p->position.y + dir_y, p->position.x + dir_x, map))
	{
		p->position.y += dir_y;
		p->position.x += dir_x;
	}
}
