/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:46:13 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 16:50:54 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 光線が当たった壁の向きを判定する関数
static void	wall_collision(t_ray *ray)
{
	// hit_vert_wallフラグで縦方向の壁かどうかを判定
	if (ray->hit_wall)
	{
		// レイの方向(x)が正なら西向きの壁
		if (ray->direction.x >= 0)
			ray->wall_dir = WEST;
		// レイの方向(x)が負なら東向きの壁
		else
			ray->wall_dir = EAST;
	}
	else
	{
		// レイの方向(y)が正なら北向きの壁
		if (ray->direction.y >= 0)
			ray->wall_dir = NORTH;
		// レイの方向(y)が負なら南向きの壁
		else
			ray->wall_dir = SOUTH;
	}
}

// 光線が壁にあたった位置を計算
static void	wall_point(t_ray *ray)
{
	// 壁の方向に応じて衝突点の位置を計算
	if (ray->wall_dir == WEST)
		ray->wall_hit_point = (int)ray->vct.y % PX;
	else if (ray->wall_dir == EAST)
		ray->wall_hit_point = PX - (((int)ray->vct.y % PX) + 1);
	else if (ray->wall_dir == NORTH)
		ray->wall_hit_point = PX - (((int)ray->vct.x % PX) + 1);
	else if (ray->wall_dir == SOUTH)
		ray->wall_hit_point = (int)ray->vct.x % PX;
}

static void	castray(t_data *data, t_ray *ray, t_player *player, double angle)
{
	int	hit_flag;

	hit_flag = 0;
	// レイの初期化
	ray->distance = 0;
	ray->wall_dir = NONE;
	ray->hit_wall = 0;
	ray->wall_hit_point = 0;
	// 光線の開始位置をプレイヤー位置に設定
	// ここがおかしそう　by trt
	ray->vct.y = player->position.y;
	ray->vct.x = player->position.x;
	ray->angle = angle;
	// レイの方向ベクトルを計算
	ray->direction.y = sin(angle);
	ray->direction.x = cos(angle);
	// 壁に当たるまでレイを進める
	while (!hit_flag)
	{
		// 次の垂直/水平グリッドラインまでの距離を計算
		ray->next_grid.y = next_grid_distance_y(ray->vct.y, angle);
		ray->next_grid.x = next_grid_distance_x(ray->vct.x, angle);
		// レイを次のグリッドラインまで進める
		increment_ray_length(ray,  get_y_step(ray->next_grid.y, ray->angle), get_x_step(ray->next_grid.x, ray->angle));
		// 壁との衝突判定（ループを抜ける）
		if (check_wall(ray->vct.y, ray->vct.x, data->map))
		{
			// どの方角の壁にあたったか判定
			wall_collision(ray);
			// 壁の位置を計算（テクスチャマッピングのための衝突点を計算）
			wall_point(ray);
			hit_flag = 1;
		}
	}
}

void	raycasting(t_data *data, t_ray *rays)
{
	double	cur_angle;
	double	delta;
	int		column_idx;

	// 初期値として視野の左端をセット　（アングル(視野中央) ー 視野角の半分）
	cur_angle = data->player.angle - (HALF_FOV);
	// 右端まで（画面の幅分）1ピクセルずつ計算する
	column_idx = 0;
	while (column_idx < WIDTH)
	{
		castray(data, &rays[column_idx], &data->player, cur_angle);
		// 魚眼効果を補正するための角度計算（0未満なら360°足す、360°超えなら360°引く）
		delta = data->player.angle - cur_angle;
		if (delta < 0)
			delta += (2 * PI);
		if (delta > (2 * PI))
			delta -= (2 * PI);
		// 魚眼補正を適用
		rays[column_idx].distance *= cos(delta);
		// 次の光線の角度を計算（0未満なら360°足す、360°超えなら360°引く）
		cur_angle += (FOV / WIDTH);
		if (cur_angle < 0)
			cur_angle += (2 * PI);
		if (cur_angle > (2 * PI))
			cur_angle -= (2 * PI);
		column_idx++;
	}
}
