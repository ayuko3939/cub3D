/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:20:19 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:07:10 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_content(t_data *data, int fd, int counter)
{
	char	*line;

	if (counter < 0)
		exit_error("Invalid file!", data);
	line = get_next_line(fd);
	// 行を取得できれば、もう一度行を読み込む
	if (line)
		get_content(data, fd, counter + 1);
	// 行を取得できない（初回）は中身がないのでエラー表示
	else if (counter == 0)
		exit_error("Invalid file!", data);
	// 行を取得できない（２回目〜）はファイルの終端なので配列の準備
	else
	{
		data->file = (char **)malloc(sizeof(char *) * (counter + 1));
		if (!data->file)
		{
			free(line);
			exit_error("error : malloc", data);
		}
		data->file[counter] = NULL;
	}
	// メモリを確保できれば行を配列にセットする
	if (data->file)
		data->file[counter] = line;
}

static void	get_file_contents(t_data *data, char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		exit_error("Invalid file path!", data);
	get_content(data, fd, 0);
	close(fd);
}

void	set_data_from_file(t_data *data, char **file)
{
	int	i;

	// スペース系を' 'に統一
	i = 0;
	while (file[i])
	{
		replace_str(file[i], "\f\r\t\v", ' ');
		replace_str(file[i], "\n", '\0');
		i++;
	}
	// 設定情報をdataに取得
	set_metadata(data, &file);
	// // 不要な行をとばす
	while (file && *file && is_str_type(*file, ft_isspace))
		file++;
	if (!*file)
		exit_error("Invalid file!", data);
	// マップの行数と最大長を取得
	data->rows = get_map_rows(file);
	data->columns = get_map_columns(file);
	if (data->rows <= 0 || data->columns <= 0)
		exit_error("Invalid map!", data);
	// マップをdataに取得
	set_map(data, file);
}

void	init_data(t_data *data, char *filepath)
{
	// 0をセットする
	setup(data);
	// ファイルの中身を配列にする
	get_file_contents(data, filepath);
	// ファイルの中身をdataに格納
	set_data_from_file(data, data->file);

	// print_map(data); // =========== test ===========
	// print_info(data); //=========== test ===========
}
