/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:45:15 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/13 18:30:37 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int	main(void)
// {
// 	const char	txt[] = {'A', 'B', 'C', 'D', 'E'};
// 	int	length;

// 	length = ft_strlen(txt);
// 	printf("length : %d\n", length);
// 	return (0);
// }