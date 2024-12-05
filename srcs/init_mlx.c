/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:48:15 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:34:32 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_data *data, t_texture *tx, char *path)
{
	tx->image.img = mlx_xpm_file_to_image(data->graphic.mlx, path, &tx->width,
			&tx->height);
	if (tx->image.img == NULL)
		exit_error("error : mlx_xpm_file_to_image", data);
	tx->image.addr = mlx_get_data_addr(tx->image.img, &tx->image.bits_per_pixel,
			&tx->image.line_size, &tx->image.endian);
	if (tx->image.addr == NULL)
		exit_error("error : mlx_get_data_addr", data);
}

void	init_mlx(t_data *data)
{
	int	i;

	// MLXの初期化
	data->graphic.mlx = mlx_init();
	if (data->graphic.mlx == NULL)
		exit_error("error : mlx_init", data);
	// テクスチャの読み込み
	i = 0;
	while (data->texture_paths[i])
	{
		load_texture(data, &data->textures[i], data->texture_paths[i]);
		i++;
	}
	// ウィンドウの作成
	data->graphic.win = mlx_new_window(data->graphic.mlx, HEIGHT, HEIGHT,
			"cub3D");
	if (data->graphic.win == NULL)
		exit_error("error : mlx_new_window", data);
	// 初期シーンの描画
	rendering(data);
}
