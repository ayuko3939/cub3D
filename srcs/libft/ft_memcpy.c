/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:02:36 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 12:19:57 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// (0)NG  (1)OK
static int	validate(void *dst, const void *src)
{
	if (dst == NULL && src == NULL)
		return (0);
	return (1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;

	if (validate(dst, src) == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

// while (n--)
// 	*destination++ = *source++;

// int	main(void)
// {
// 	char name1[21] = "Johnnys Entertainment";
// 	char name2[21] = "Johnnys Entertainment";
// 	char name3[21] = "STARTO ENTERTAINMENT";

// 	printf("Before : %s\n", name1);
// 	ft_memcpy(name1, name3, (sizeof(name3) / sizeof(char)));
// 	memcpy(name2, name3, (sizeof(name3) / sizeof(char)));
// 	printf("ft_memcpy : %s\n", name1);
// 	printf("   memcpy : %s\n", name2);
// 	return (0);
// }