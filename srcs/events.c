/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:57:56 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:35:19 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(t_player *p, int key, char **map)
{
	int	i;

	i = 0;
	// 方角に合わせたｙ、ｘ（北(-1,0)、南(1,0)、東(0,1)、西(0,-1)）で現在地を動かす
	while (i < PACE)
	{
		// 前
		if (key == W)
			move_player(p, p->direction.y, p->direction.x, map);
		// 後
		else if (key == S)
			move_player(p, -p->direction.y, -p->direction.x, map);
		// 左
		else if (key == A)
			move_player(p, -p->direction.x, p->direction.y, map);
		// 右
		else if (key == D)
			move_player(p, p->direction.x, -p->direction.y, map);
		i++;
	}
}

static void	handle_left_angle(t_player *p)
{
	// アングルを固定値（0.1）ずつ右へ動かす
	p->angle -= TURNANGLE;
	// 360超になったら360度引く
	if (p->angle < 0)
		p->angle += (2 * PI);
	p->direction.y = sin(p->angle);
	p->direction.x = cos(p->angle);
}

static void	handle_right_angle(t_player *p)
{
	// アングルを固定値（0.1）ずつ右へ動かす
	p->angle += TURNANGLE;
	// 360超になったら360度引く
	if (p->angle > (2 * PI))
		p->angle -= (2 * PI);
	p->direction.y = sin(p->angle);
	p->direction.x = cos(p->angle);
}

// (true)show minimap  (false)hide minimap
static void	minimap_swich(t_data *data)
{
	// ミニマップの表示・非表示を反転させる
	data->show_minimap = !data->show_minimap;
}

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		exit_game(data);
	else
	{
		if (key == W || key == S || key == A || key == D)
			handle_movement(&data->player, key, data->map);
		else if (key == LA)
			handle_left_angle(&data->player);
		else if (key == RA)
			handle_right_angle(&data->player);
		else if (key == M)
			minimap_swich(data);
		rendering(data);
	}
	return (0);
}
