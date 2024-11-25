/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:50:23 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/14 17:43:55 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>

char	*free_nullset(char **str);
int		read_from_fd(int fd, char **temp);
char	*get_newline(char *str);
int		remove_line_from_temp(char **str);
char	*get_next_line(int fd);

size_t	gnl_strlen(const char *str);
int		gnl_strchr(const char *s, int c);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
int		gnl_strjoin(char **s1, char *s2);

#endif
