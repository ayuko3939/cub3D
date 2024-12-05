/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:33:16 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:43:59 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_new_image(t_data *data, t_window *g)
{
	// 現在の描画を削除
	if (g->image.img)
		mlx_destroy_image(g->mlx, g->image.img);
	// 新しく描画し直し
	g->image.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (g->image.img == NULL)
		exit_error("error : mlx_new_image", data);
	// イメージのメモリアドレスを取得
	g->image.addr = mlx_get_data_addr(g->image.img, &g->image.bits_per_pixel,
			&g->image.line_size, &g->image.endian);
}

void	rendering(t_data *data)
{
	t_window	*graphic;

	graphic = &data->graphic;
	// レイ配列の確保（画面の幅分のレイを生成）
	data->rays = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
	if (data->rays == NULL)
		exit_error("error : malloc", data);
	// 新しいフレーム用のイメージを作成
	create_new_image(data, graphic);
	// レイキャスティングを実行
	raycasting(data, data->rays);
	// 床と天井を描画
	draw_floor_and_ceiling(data);
	// 壁を描画
	draw_walls(data, data->rays);
	// ミニマップを表示（有効な場合）
	if (data->show_minimap)
		draw_minimap(data, graphic);
	// レイ配列の解放
	free(data->rays);
	// イメージをウィンドウに配置する
	mlx_put_image_to_window(graphic->mlx, graphic->win, graphic->image.img, 0,
		0);
}
