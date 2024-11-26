/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:41:14 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/26 15:06:21 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

bool	is_include_char(char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	if (c == '\0')
		return (true);
	return (false);
}

void	replace_str(char *str, char *remove, char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_include_char(remove, str[i]))
			str[i] = replace;
		i++;
	}
}

int	strarr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

bool	is_str_type(char *str, int (*function)(int))
{
	size_t	i;

	if (!str || !function)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!function(str[i]))
			return (false);
		i++;
	}
	return (true);
}
