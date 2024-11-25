/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohasega <yohasega@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:10:00 by yohasega          #+#    #+#             */
/*   Updated: 2024/08/04 19:47:14 by yohasega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// (0)NG  (1)OK
static int	validate(size_t count, size_t size)
{
	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	if (validate(count, size) == 0)
		return (NULL);
	array = malloc(count * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, count * size);
	return (array);
}

// ===== without ft_bzero =====
// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*array;
// 	size_t		i;

// 	if (validate(count, size) == 0)
// 		return (NULL);
// 	array = malloc(count * size);
// 	if (array == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < size)
// 	{
// 		((char *)array)[i] = 0;
// 		i++;
// 	}
// 	return (array);
// }

// int	main(void)
// {
// 	int n = 0;
// 	int i;
// 	int *array1;
// 	int *array2;

// 	array1 = (int *)ft_calloc(0, 0);
// 	array2 = (int *)calloc(0, 0);
// 	if (array1 == NULL)
// 	{
// 		printf("1error\n");
// 		return (1);
// 	}
// 	if (array2 == NULL)
// 	{
// 		printf("2error\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (i < n)
// 	{
// 		printf("%d ", array1[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	i = 0;
// 	while (i < n)
// 	{
// 		printf("%d ", array2[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	free(array1);
// 	free(array2);
// 	return (0);
// }