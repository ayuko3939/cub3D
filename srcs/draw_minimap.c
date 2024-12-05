/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:58:27 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 16:06:37 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	// マップスケールに応じたサイズの四角形を描画
	while (i < data->minimap_scale)
	{
		j = 0;
		while (j < data->minimap_scale)
		{
			// 四角形の外周は藍色で描画、中は指定の色で描画
			if (i == 0 || j == 0 || i == data->minimap_scale - 1
				|| j == data->minimap_scale - 1)
				image_pixel_put(&data->graphic.image, x + i, y + j, NAVY);
			else
				image_pixel_put(&data->graphic.image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_grid(t_data *data)
{
	int		y;
	int		x;
	char	cell;

	y = 0;
	while (y < data->rows)
	{
		x = 0;
		while (x < data->columns - 1)
		{
			// マップデータのセルを取得
			cell = data->map[y][x];
			// セルが壁なら黒色で四角く塗りつぶす
			if (cell == '1' || cell == ' ')
				draw_square(data, x * data->minimap_scale, y
					* data->minimap_scale, BLACK);
			// セルが床なら灰色で四角く塗りつぶす
			else if (cell == '0' || ft_strchr("NSWE", cell))
				draw_square(data, x * data->minimap_scale, y
					* data->minimap_scale, LIGHT_GREY);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_image *image, t_player *p, int minimap_scale)
{
	float		px_division;
	t_vct_int	player;
	t_vct_int	draw;

	// 縮尺を計算
	px_division = (float)PX / minimap_scale;
	// プレイヤーの実座標をミニマップ上の座標に変換
	player.x = round(p->position.x / px_division);
	player.y = round(p->position.y / px_division);
	draw.y = 0;
	// プレイヤーを橙色の四角形として描画
	while (draw.y < PLYLEN)
	{
		draw.x = 0;
		while (draw.x < PLYLEN)
		{
			image_pixel_put(image, player.x + draw.x - (PLYLEN / 2),
				player.y + draw.y - (PLYLEN / 2), ORANGE);
			draw.x++;
		}
		draw.y++;
	}
}

void	draw_minimap(t_data *data, t_window *graphic)
{
	// ミニマップの縮尺を計算
	data->minimap_scale = HEIGHT / (3 * data->rows);
	// ミニマップのグリッド（マップの壁と空間）を描画
	draw_grid(data);
	// ミニマップ上のプレイヤーを描画
	draw_player(&graphic->image, &data->player, data->minimap_scale);
	// 描画したイメージをウィンドウに表示
	mlx_put_image_to_window(graphic->mlx, graphic->win, graphic->image.img, 0,
		0);
}
