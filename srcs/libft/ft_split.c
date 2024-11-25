/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:30:48 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 18:55:27 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s != 0)
			count++;
		while (*s != c && *s != 0)
			s++;
	}
	return (count);
}

static void	free_all(char **array)
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

static	char	**get_words(char **array, char const *s, char c, size_t count)
{
	size_t	ary_i;
	size_t	str_i;
	size_t	start;

	ary_i = 0;
	str_i = 0;
	start = 0;
	while (ary_i < count)
	{
		while (s[str_i] == c)
			str_i++;
		start = str_i;
		while (s[str_i] != c && s[str_i] != 0)
			str_i++;
		array[ary_i] = ft_substr(s, start, str_i - start);
		if (array[ary_i] == NULL)
		{
			free_all(array);
			return (NULL);
		}
		ary_i++;
	}
	array[ary_i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	count;

	if (s == NULL || *s == 0)
	{
		array = (char **)malloc(sizeof(char *) * 1);
		array[0] = NULL;
		return (array);
	}
	if (c == 0)
	{
		array = (char **)malloc(sizeof(char *) * 2);
		array[0] = ft_strdup(s);
		array[1] = NULL;
		return (array);
	}
	count = count_word(s, c);
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (array == NULL)
		return (NULL);
	array = get_words(array, s, c, count);
	return (array);
}

// int	main(void)
// {
// 	char const *str = "";
// 	char delimiter = {'a'};
// 	char **array;
// 	int i;

// 	printf("before : %s\n", str);
// 	array = ft_split(str, delimiter);
// 	printf("after  : \n");
// 	i = 0;
// 	while (*array != NULL)
// 	{
// 		printf("%s\n", array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }

//ccw ft_split.c ft_strdup.c ft_substr.c ft_calloc.c ft_memcpy.c
// ft_strlcpy.c ft_strlen.c ft_bzero.c ft_memset.c