/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:49:03 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 15:01:37 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_size + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_data *data, int y, int offset_x, t_ray ray)
{
	t_texture	txtr;
	t_vct_int	offset;
	int			dist_to_top;
	int			color;

	// どの方角の壁のテクスチャを使うか選択
	txtr = data->textures[ray.wall_dir];
	// テクスチャの横位置
	offset.x = offset_x;
	// 壁の高さに応じてテクスチャのY座標を計算
	dist_to_top = y + (ray.wall_height / 2) - (HEIGHT / 2);
	offset.y = (dist_to_top * ((double)txtr.height / ray.wall_height));
	// テクスチャの色を取得
	color = *(unsigned int *)(txtr.image.addr + (offset.y * txtr.image.line_size + offset.x * (txtr.image.bits_per_pixel / 8)));
	return (color);
}
