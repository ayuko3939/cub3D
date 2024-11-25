/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:49:42 by yohasega          #+#    #+#             */
/*   Updated: 2024/07/16 19:01:45 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// calloc var
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s1);
	str = (char *)ft_calloc(1, sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, len);
	return (str);
}

// malloc ver
// char	*ft_strdup(const char *s1)
// {
// 	size_t	len;
// 	char	*str;

// 	len = ft_strlen(s1);
// 	str = malloc(sizeof(char) * (len + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	ft_strlcpy(str, s1, len + 1);
// 	return (str);
// }

// int	main(void)
// {
// 	const char str[] = "Snow Man";
// 	char *newstr1;
// 	char *newstr2;

// 	newstr1 = ft_strdup(str);
// 	if (newstr1 != NULL)
// 		printf("ft_strdup:%s\n", newstr1);
// 	newstr2 = strdup(str);
// 	if (newstr2 != NULL)
// 		printf("   strdup:%s\n", strdup(str));
//     free(newstr1);
//     free(newstr2);
// 	return (0);
// }