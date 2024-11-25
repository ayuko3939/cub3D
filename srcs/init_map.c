/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:54:58 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/24 14:43:39 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// -1 : error
int	get_map_columns(char **file)
{
	int	columns;
	
	columns = 0;
	while (file && *file)
	{
		// より長い行があれば値を更新する（\0文字分を足しておく）
		if ((int)ft_strlen(*file) > columns)
			columns = (int)ft_strlen(*file) + 1;
		file++;
	}
	return (columns);
}

// -1 : error
int	get_map_rows(char **file)
{
	int	rows;

	rows = 0;
	while (file && file[rows])
	{
		// 途中で空白行があればエラー判定
		if (is_str_type(file[rows], ft_isspace))
			return (-1);
		rows++;
	}
	return (rows);
}

void	set_map(t_data *data, char **file)
{
	int	i;
	int	j;

	// マップ（全体）のメモリを確保
	data->map = (char **)ft_calloc(data->rows + 1, sizeof(char *));
	if (!data->map)
		exit_error("error : malloc", data);
	// マップを取得
	i = 0;
	while (i < data->rows)
	{
		// マップ（各行）のメモリを確保
		data->map[i] = (char *)ft_calloc(data->columns + 1, sizeof(char));
		if (!data->map[i])
			exit_error("error : malloc", data);
		j = 0;
		// コピー
		while (file[i][j])
		{
			data->map[i][j] = file[i][j];
			j++;
		}
		// 残りはスペースで埋める（\0だと探索の時にセグフォするため）
		while (j < data->columns - 1)
		{
			data->map[i][j] = ' ';
			j++;
		}
		i++;
	}
}
