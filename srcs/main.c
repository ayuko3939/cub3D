/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:39:56 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 15:47:58 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate(int ac, char **av)
{
	char	*extension;

	if (ac != 2)
	{
		error_print("Invalid argument!");
		return (EXIT_FAILURE);
	}
	extension = ft_strchr(av[1], '.');
	if (!extension || ft_strcmp(extension, ".cub"))
	{
		error_print("Invalid map file!");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	// 引数チェック
	if (validate(ac, av))
		return (EXIT_FAILURE);
	// ファイルから情報を取得してdataに格納
	init_data(&data, av[1]);
	// マップの内容確認
	check_map(&data);
	// MLXの初期化とウィンドウ作成
	init_mlx(&data);
	// キー入力の設定（イベント 2:キー押下   マスク 1L<<0:キープレスマスク）
	mlx_hook(data.graphic.win, 2, 1L << 0, key_press, &data);
	// ウィンドウ×ボタンの設定（イベント 17:破棄通知   マスク 0L:イベントマスクなし）
	mlx_hook(data.graphic.win, 17, 0L, (void *)exit_game, &data);
	// ループ処理
	mlx_loop(data.graphic.mlx);
}
