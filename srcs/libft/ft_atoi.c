/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:45:01 by yohasega          #+#    #+#             */
/*   Updated: 2024/05/09 12:00:32 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*remove_space(const char *s)
{
	while (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\f' || *s == '\r'
		|| *s == ' ')
		s++;
	return ((char *)s);
}

static	long	ft_strtol(const char *str)
{
	long	lnum;
	int		sign;

	lnum = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		if (lnum > LONG_MAX / 10
			|| (lnum == LONG_MAX / 10 && (*str - '0') > LONG_MAX % 10))
		{
			if (sign < 0)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		lnum = lnum * 10 + (*str - '0');
		str++;
	}
	lnum = lnum * sign;
	return (lnum);
}

int	ft_atoi(const char *str)
{
	int			num;
	const char	*st;

	st = remove_space(str);
	num = (int)ft_strtol(st);
	return (num);
}

// int	main(void)
// {
// 	char *nm = "-9223372036854775807";

// 	printf("ft_atoi : %d\n", ft_atoi(nm));
// 	printf("   atoi : %d\n", atoi(nm));
// 	return (0);
// }