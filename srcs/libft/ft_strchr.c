/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:24:05 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/13 18:30:25 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

//======================== another code ========================
// char	*ft_strchr(const char *s, int c)
// {
// 	size_t	count;

// 	count = 0;
// 	c = (char)c;
// 	while (count != strlen(s) + 1)
// 	{
// 		if (*s == c)
// 			return ((char *)s);
// 		count++;
// 		s++;
// 	}
// 	return (NULL);
// }
//======================== model answer ========================
// char	*ft_strchr(const char *s, int c)
// {
//     c = (char)c;
// 	while (*s != c)
// 	{
// 		if (*s == '\0')
// 			return (NULL);
// 		s++;
// 	}
// 	return ((char *)s);
// }
//==============================================================

// int	main(void)
// {
// 	char str[] = "Snow Man";

// 	printf("ft_strchr : %s\n", ft_strchr(str, '\0'));
// 	printf("   strchr : %s\n", strchr(str, '\0'));
// 	return (0);
// }