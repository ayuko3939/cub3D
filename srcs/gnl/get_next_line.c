/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:49:42 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/14 17:43:39 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_nullset(char **str)
{
	if (*str == NULL)
		return (*str);
	free(*str);
	*str = NULL;
	return (*str);
}

// (0)NG  (1)OK
int	read_from_fd(int fd, char **temp)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	while (gnl_strchr(*temp, '\n') == 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free_nullset(&buf);
			free_nullset(temp);
			return (0);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		if (gnl_strjoin(temp, buf) == 0)
			return (0);
	}
	free_nullset(&buf);
	return (1);
}

char	*get_newline(char *str)
{
	size_t	len;
	char	*line;

	len = 0;
	if (str == NULL || *str == 0)
		return (NULL);
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (line == NULL)
		return (NULL);
	gnl_strlcpy(line, str, len + 2);
	return (line);
}

// (0)NG  (1)OK
int	remove_line_from_temp(char **str)
{
	size_t	len;
	char	*new_temp;

	len = 0;
	while ((*str)[len] != '\0' && (*str)[len] != '\n')
		len++;
	len++;
	new_temp = gnl_substr(*str, len, gnl_strlen(*str) - len);
	if (new_temp == NULL)
		return (0);
	free(*str);
	*str = new_temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*temp_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (gnl_strchr(temp_str, '\n') == 0)
	{
		if (read_from_fd(fd, &temp_str) == 0)
			return (NULL);
	}
	line = get_newline(temp_str);
	if (line == NULL)
		return (free_nullset(&temp_str));
	if (remove_line_from_temp(&temp_str) == 0)
	{
		free_nullset(&temp_str);
		return (free_nullset(&line));
	}
	return (line);
}

// #include <fcntl.h> // open
// #include <stdio.h> // printf

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("get_next_line.c", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 		if (line == NULL)
// 			break;
// 	}
// 	close(fd);
// 	return (0);
// }
