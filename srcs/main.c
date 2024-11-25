/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:39:56 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/25 13:58:45 by yohasega         ###   ########.fr       */
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

// =========================== exit ===========================

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture_paths[i])
			free(data->texture_paths[i]);
		i++;
	}
	if (data->file)
		free_all(data->file);
	if (data->map)
		free_all(data->map);
	
	// mlx
	// if (data->graphic.image.img)
	// 	mlx_destroy_image(data->graphic.mlx, data->graphic.image.img);
	// if (data->graphic.win)
	// 	mlx_destroy_window(data->graphic.mlx, data->graphic.win);
	// if (data->graphic.mlx)
	// {
	// 	mlx_destroy_display(data->graphic.mlx);
	// 	free(data->graphic.mlx);
	// }
}

void	error_print(char *message)
{
	if (message)
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd(END, STDERR_FILENO);
	}
}

void	exit_error(char *message, t_data *data)
{
	// メモリ開放
	free_data(data);
	// エラーメッセージ出力
	if (message)
		error_print(message);
	exit(EXIT_FAILURE);
}

// =========================== init_mlx ===========================

// void	image_pixel_put(t_image *data, int x, int y, int color)
// {
// 	char	*dst;
// 	dst = data->addr + (y * data->line_size + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

// void	init_mlx(t_data *data)
// {
// 	// MLXの初期化
// 	data->graphic.mlx = mlx_init();
// 	if (data->graphic.mlx == NULL)
// 		exit_error("error : mlx_init", data);
// 	// テクスチャの読み込み
// 	// load_textures(data);  // 未作成！！！！
// 	// ウィンドウの作成
// 	data->graphic.win = mlx_new_window(data->graphic.mlx, HEIGHT, HEIGHT, "cub3D");
// 	if (data->graphic.win == NULL)
// 		exit_error("error : mlx_new_window", data);
// 	// 初期シーンの描画
// 	// rendering(data);  // 未作成！！！！
// }


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
	// init_mlx(&data);

// printf(ORANGE);
// // ======================== test ========================
	// printf("NORTH : %s\n",data->texture_paths[NORTH]);
	// printf("SOUTH : %s\n",data->texture_paths[SOUTH]);
	// printf(" WEST : %s\n",data->texture_paths[WEST]);
	// printf(" EAST : %s\n",data->texture_paths[EAST]);
	// printf("C [0] : %d\n",data->ceiling_rgb[0]);
	// printf("C [1] : %d\n",data->ceiling_rgb[1]);
	// printf("C [2] : %d\n",data->ceiling_rgb[2]);
	// printf("F [0] : %d\n",data->floor_rgb[0]);
	// printf("F [1] : %d\n",data->floor_rgb[1]);
	// printf("F [2] : %d\n",data->floor_rgb[2]);
// // ======================== test ========================
// int i = 0;
// char *str;
// while (data->map[i])
// {
// 	str = data->map[i];
// 	printf("%s", str);
// 	printf("\n");
// 	i++;
// }
// // ======================== test ========================
	// printf("map rows    : %d\n",data->rows);
	// printf("map columns : %d\n",data->columns);
// // ======================== test ========================
// printf(END);


	free_data(&data);	// 最後に消す
	return (EXIT_SUCCESS);
}
