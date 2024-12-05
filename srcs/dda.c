/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:26:57 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:35:59 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// @brief レイの垂直方向の次のグリッドラインまでの距離を計算
// @param y 現在のY座標
// @param angle レイの角度
// @return 次のグリッドラインまでの距離
double	next_grid_distance_y(int y, double angle)
{
	int		i;
	double	distance;

	i = 0;
	distance = 0;
	// ほぼ真東またはほぼ真西の場合は距離0
	if (fabs(angle - 0) < TOLERANCE || fabs(angle - PI) < TOLERANCE)
		return (0);
	// 南（上）向きの場合(2πで360°なので180°未満の時)
	if (angle < PI)
	{
		while ((i * PX) <= y)
			i++;
		distance = (i * PX) - y;
	}
	// 北（下）向きの場合(2πで360°なので180°超の時)
	else if (angle > PI)
	{
		while ((i * PX) <= y)
			i++;
		i--;
		distance = y - (i * PX) + 1;
	}
	return (distance);
}

// @brief レイの垂直方向の次のグリッドラインまでの距離を計算
// @param x 現在のX座標
// @param angle レイの角度
// @return 次のグリッドラインまでの距離
double	next_grid_distance_x(int x, double angle)
{
	int		i;
	double	distance;

	i = 0;
	distance = 0;
	// 西（右）向きの場合（南90°〜北270°の間）
	if (angle > (PI / 2) && angle < ((3 * PI) / 2))
	{
		while ((i * PX) <= x)
			i++;
		i--;
		distance = x - (i * PX) + 1;
	}
	// 東（左）向きの場合（〜南90°または北270°〜）
	else if (angle < (PI / 2) || angle > ((3 * PI) / 2))
	{
		while ((i * PX) <= x)
			i++;
		distance = (i * PX) - x;
	}
	return (distance);
}

// @brief 指定された角度に基づいて次のグリッドラインまでの垂直方向の距離を計算
// @param opose 対辺の長さ
// @param angle 角度（ラジアン）
// @return 次のグリッドラインまでの距離
double	get_y_step(int opose, double angle)
{
	double	distance;
	int		int_angle;
	int		angle_0;
	int		angle_180;

	distance = 0;
	// 角度の精度を高めるため、大きな数を掛ける
	int_angle = (double)(angle * 10000000);
	angle_180 = (double)(PI * 10000000) + 1;
	angle_0 = 0;
	// 水平方向(180度または0度)の場合は0を返す
	if (int_angle == angle_0 || int_angle == angle_180)
		return (0);
	// 三角関数を使用して距離を計算（対辺 ÷ sinθ = 外接円の直径）
	distance = fabs(opose / sin(angle));
	return (distance);
}

// @brief 指定された角度に基づいて次のグリッドラインまでの水平方向の距離を計算
// @param adj 隣辺の長さ
// @param angle 角度（ラジアン）
// @return 次のグリッドラインまでの距離
double	get_x_step(int adj, double angle)
{
	double	distance;
	int		int_angle;
	int		angle_90;
	int		angle_270;

	distance = 0;
	// 角度の精度を高めるため、大きな数を掛ける
	int_angle = (double)(angle * 10000000) - 1;
	angle_90 = (double)((PI / 2) * 10000000);
	angle_270 = (double)(((3 * PI) / 2) * 10000000);
	// 水平方向(180度または0度)の場合は0を返す
	if (int_angle == angle_90 || int_angle == angle_270)
		return (0);
	// 三角関数を使用して距離を計算（隣辺 ÷ cosθ = 斜辺）
	distance = fabs(adj / cos(angle));
	return (distance);
}

// @brief レイの長さを増加させ、次のグリッドラインまでの距離を計算
// @param ray レイの情報を持つ構造体
// @param step_y Y方向のステップ
// @param step_x X方向のステップ
void	increment_ray_length(t_ray *ray, double step_y, double step_x)
{
	// X方向のステップが存在しない場合、またはY方向のステップが短い場合
	if (step_x == 0 || (step_y && step_y <= step_x))
	{
		// レイの方向に応じてY座標を更新
		if (ray->direction.y < 0)
			ray->vct.y -= ray->next_grid.y;
		else
			ray->vct.y += ray->next_grid.y;
		// X座標を更新
		ray->vct.x += step_y * ray->direction.x;
		ray->distance += step_y;
		ray->hit_wall = 0;
	}
	else if (step_y == 0 || (step_x && step_y > step_x))
	{
		// レイの方向に応じてX座標を更新
		if (ray->direction.x < 0)
			ray->vct.x -= ray->next_grid.x;
		else
			ray->vct.x += ray->next_grid.x;
		// Y座標を更新
		ray->vct.y += step_x * ray->direction.y;
		ray->distance += step_x;
		ray->hit_wall = 1;
	}
}
