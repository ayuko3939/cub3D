/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:17:01 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 12:00:35 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

//======================== another code ========================
// void	ft_bzero(void *s, size_t n)
// {
// 	size_t	i;
// 	char	*st;

// 	st = (char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		st[i] = '\0';
// 		i++;
// 	}
// }
//==============================================================

// int	main(void)
// {
// 	char name1[21] = "Johnnys Entertainment";
// 	char name2[21] = "Johnnys Entertainment";

// 	printf("Before : %s\n", name1);
//  ft_bzero(name1, (sizeof(name1) / sizeof(char)));
// 	bzero(name2, (sizeof(name1) / sizeof(char)));
// 	printf("ft_bzero : %s\n", name1);
// 	printf("   bzero : %s\n", name2);
// 	return (0);
// }