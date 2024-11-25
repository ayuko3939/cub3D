/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:45:25 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/20 21:15:45 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	i = 0;
// 	while (i < n && (str1[i] || str2[i]))
// 	{
// 		if (str1[i] != str2[i])
// 			return (str1[i] - str2[i]);
// 		i++;
// 	}
// 	return (0);
// }

//======================== model answer ========================
// int		ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	while (n && *s1 && *s2)
// 	{
// 		if (*s1 != *s2)
// 			return ((unsigned char)*s1 -(unsigned char)*s2);
// 		s1++;
// 		s2++;
// 		n--;
// 	}
// 	if (!n)
// 		return (0);
// 	// if (*s1)
// 	// 	return (1);
// 	// return (-1);
// }
//==============================================================

// int	main(void)
// {
// 	const char str1[] = "Snow Man";
// 	const char str2[] = "Snow man";

// 	printf("ft_strncmp:%d\n", ft_strncmp(str1, str2, 6));
// 	printf("   strncmp:%d\n", strncmp(str1, str2, 6));
// 	return (0);
// }