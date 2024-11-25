/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:44:51 by yohasega          #+#    #+#             */
/*   Updated: 2024/11/13 16:54:36 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// (0)NG  (1)OK
static int	validate(char const *s, unsigned int start, size_t len)
{
	if (s == 0 || len == 0)
		return (0);
	if (ft_strlen(s) < start)
		return (0);
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char const		*substr;
	size_t			len_s;

	if (validate(s, start, len) == 0)
	{
		substr = ft_calloc(1, sizeof(char) * 1);
		return ((char *)substr);
	}
	s = s + start;
	len_s = ft_strlen(s);
	if (len_s < len)
		len = len_s;
	substr = ft_calloc(1, sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	ft_memcpy((void *)substr, s, len);
	return ((char *)substr);
}

// int	main(void)
// {
// 	char const *str = "asdfghjkl";
// 	char const *substring = NULL;
// 	size_t len = 3;

// 	substring = ft_substr(str, 3, len);
// 	printf("%s\n", substring);
// 	return (0);
// }