/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:48:18 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 14:59:37 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_column(t_data *data, t_ray ray, t_vct_int start, int end_y)
{
	int	color;
	int	y;

	y = start.y;
	while (y < end_y)
	{
		color = get_texture_color(data, y, ray.wall_hit_point, ray);
		image_pixel_put(&data->graphic.image, start.x, y, color);
		y++;
	}
}

// 3D視点の壁を描画する
void	draw_walls(t_data *data, t_ray *rays)
{
	int			x;
	t_vct_int	start;
	int			end_y;

	x = 0;
	// 画面の各列について壁を描画
	while (x < WIDTH)
	{
		// 壁の高さを計算（距離に応じて調整）
		rays[x].wall_height = ((PX / rays[x].distance) * PLANE_DIST);
		start.x = x;
		// 壁の開始Y座標を計算
		start.y = floor(HEIGHT / 2) - (rays[x].wall_height / 2);
		if (start.y < 0)
			start.y = 0;
		// 壁の終了Y座標を計算
		end_y = floor(HEIGHT / 2) + (rays[x].wall_height / 2);
		if (end_y >= HEIGHT)
			end_y = HEIGHT - 1;
		// 壁の列を描画
		draw_wall_column(data, rays[x], start, end_y);
		x++;
	}
}
static int	rgb_to_int(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	color_fill(t_data *data, int start_y, int end_y, int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			image_pixel_put(&data->graphic.image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor_and_ceiling(t_data *data)
{
	int	color;

	// 天井のRGB値を整数値に変換して描画
	color = rgb_to_int(data->ceiling_rgb[0], data->ceiling_rgb[1], data->ceiling_rgb[2]);
	color_fill(data, 0, HEIGHT / 2, color);
	// 床のRGB値を整数値に変換して描画
	color = rgb_to_int(data->floor_rgb[0], data->floor_rgb[1], data->floor_rgb[2]);
	color_fill(data, HEIGHT / 2, HEIGHT, color);
}
