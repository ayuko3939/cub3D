/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:23:02 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 12:00:22 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// int	main(void)
// {
// 	int s = '\0';

// 	printf("ft_isdigit : %d\n", ft_isdigit(s));
// 	printf("   isdigit : %d\n", isdigit(s));
// 	return (0);
// }