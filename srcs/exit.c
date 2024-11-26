/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:30:04 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 15:32:52 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture_paths[i])
			free(data->texture_paths[i]);
		// 各テクスチャのmlx情報
		if (data->textures[i].image.img)
			mlx_destroy_image(data->graphic.mlx, data->textures[i].image.img);
		i++;
	}
	if (data->file)
		free_all(data->file);
	if (data->map)
		free_all(data->map);
	
	// mlx
	if (data->graphic.image.img)
		mlx_destroy_image(data->graphic.mlx, data->graphic.image.img);
	if (data->graphic.win)
		mlx_destroy_window(data->graphic.mlx, data->graphic.win);
	if (data->graphic.mlx)
	{
		mlx_destroy_display(data->graphic.mlx);
		free(data->graphic.mlx);
	}
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

void	exit_game(t_data *data)
{
	// メモリ開放
	free_data(data);
	// あいさつ
	ft_putstr_fd(VIOLET, STDERR_FILENO);
	ft_putstr_fd("*.+ THANKS FOR PLAYING! SEE YOU SOON! +.*", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(END, STDERR_FILENO);
	exit(EXIT_SUCCESS);
}
