/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:09:26 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 13:28:22 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)buf;
	i = 0;
	while (i < n)
	{
		s[i] = (unsigned char)ch;
		i++;
	}
	return (buf);
}

// int	main(void)
// {
// 	char name1[21] = "Johnnys Entertainment";
// 	char name2[21] = "Johnnys Entertainment";

// 	printf("Before : %s\n", name1);
// 	ft_memset(name1, '-', (sizeof(name1) / sizeof(char)));
// 	memset(name2, '-', (sizeof(name1) / sizeof(char)));
// 	printf("ft_memset : %s\n", name1);
// 	printf("   memset : %s\n", name2);
// 	return (0);
// }