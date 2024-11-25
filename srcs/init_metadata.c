/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:55:59 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/23 20:17:35 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_rgv_value(char **numbers, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		// 文字列が3桁以上、または数字以外の文字を含む場合、エラー
		if (ft_strlen(numbers[i]) > 3 || !is_str_type(numbers[i], ft_isdigit))
			return (EXIT_FAILURE);
		rgb[i] = ft_atoi(numbers[i]);
		// RGB値（０〜２５５）でない場合、エラー
		if (rgb[i] < 0 || rgb[i] > 255)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	set_rgb(int *rgb, char *splited)
{
	char	**numbers;

	// rgbの中身がない（「C」または「F」のみの場合）
	if (!splited)
		return (EXIT_FAILURE);
	else
	{
		// rgb値をカンマ区切りで取得
		numbers = ft_split(splited, ',');
		// rgb値が３つじゃない、または不正な値だったらエラー、問題なければ値をセット
		if (strarr_size(numbers) != 3 || set_rgv_value(numbers, rgb))
		{
			free_all(numbers);
			error_print("Invalid rgb value!");
			return (EXIT_FAILURE);
		}
		free_all(numbers);
	}
	return (EXIT_SUCCESS);
}

static int	set_texture_path(t_data *data, int dir, char *path)
{
	int	fd;

	// テクスチャファイルを読み込み専用で開く
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_print("Invalid texture path!");
		return (EXIT_FAILURE);
	}
	// 正常に開けた場合はテクスチャパスを保存
	data->texture_paths[dir] = ft_strdup(path);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	handle_metadata(t_data *data, char **splited)
{
	// 壁（北、南、西、東）の行なら、テクスチャファイルを確認
	if (!ft_strcmp(splited[0], "NO"))
		return (set_texture_path(data, NORTH, splited[1]));
	else if (!ft_strcmp(splited[0], "SO"))
		return (set_texture_path(data, SOUTH, splited[1]));
	else if (!ft_strcmp(splited[0], "WE"))
		return (set_texture_path(data, WEST, splited[1]));
	else if (!ft_strcmp(splited[0], "EA"))
		return (set_texture_path(data, EAST, splited[1]));
	// 天井 / 床の行ならRGBを確認
	else if (!ft_strcmp(splited[0], "C"))
		return (set_rgb(data->ceiling_rgb, splited[1]));
	else if (!ft_strcmp(splited[0], "F"))
		return (set_rgb(data->floor_rgb, splited[1]));
	// 空白行 / マップなら何もしない
	return (EXIT_SUCCESS);
}

void	set_metadata(t_data *data, char ***file)
{
	char	**split_line;

	while (*file && **file)
	{
		// スペースで分ける「NO ./NO.xpm」->「NO」「./NO.xpm」、「F 20,100,0」->「F」「20,100,0」
		split_line = ft_split(**file, ' ');
		if (split_line && split_line[0])
		{
			if (handle_metadata(data, split_line))
			{
				free_all(split_line);
				exit_error(NULL, data);
			}
		}
		free_all(split_line);
		// fileを進めて読み終わった部分をとばす（最終的にマップ部分が残る）
		(*file)++;
		// メタデータの設定が終わったら処理終了
		if (strarr_size(data->texture_paths) == 4
			&& data->ceiling_rgb[0] != -1 && data->floor_rgb[0] != -1)
			break ;
	}
}
