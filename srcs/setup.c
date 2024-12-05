/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:06:37 by yohasega          #+#    #+#             */
/*   Updated: 2024/12/05 15:53:22 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->texture_paths[i] = NULL;
		data->textures[i].width = 0;				// なくてもいい
		data->textures[i].height = 0;				// なくてもいい
		data->textures[i].image.img = NULL;
		data->textures[i].image.addr = NULL;		// なくてもいい
		data->textures[i].image.bits_per_pixel = 0;	// なくてもいい
		data->textures[i].image.endian = 0;			// なくてもいい
		data->textures[i].image.line_size = 0;		// なくてもいい
		i++;
	}
}

static void	setup_map_info(t_data *data)
{
	data->file = NULL;
	data->floor_rgb[0] = -1;
	data->floor_rgb[1] = -1;
	data->floor_rgb[2] = -1;
	data->ceiling_rgb[0] = -1;
	data->ceiling_rgb[1] = -1;
	data->ceiling_rgb[2] = -1;
	data->map = NULL;
	data->rows = 0;
	data->columns = 0;
	data->rays = NULL;				// なくてもいい
	data->show_minimap = false;
	data->minimap_scale = 0;		// なくてもいい
}

static void	setup_player(t_player *player)
{
	player->position.x = 0;		// なくてもいい
	player->position.y = 0;		// なくてもいい
	player->array_pos.x = 0;	// なくてもいい
	player->array_pos.y = 0;	// なくてもいい
	player->direction.x = 0;	// なくてもいい
	player->direction.y = 0;	// なくてもいい
	player->angle = 0;			// なくてもいい
}

static void	setup_graphic(t_window *graphic)
{
	graphic->mlx = NULL;
	graphic->win = NULL;
	graphic->image.img = NULL;
	graphic->image.addr = NULL;			// なくてもいい
	graphic->image.bits_per_pixel = 0;	// なくてもいい
	graphic->image.endian = 0;			// なくてもいい
	graphic->image.line_size = 0;		// なくてもいい
}

void	setup(t_data *data)
{
	setup_map_info(data);
	setup_texture(data);
	setup_player(&data->player);
	setup_graphic(&data->graphic);
}
