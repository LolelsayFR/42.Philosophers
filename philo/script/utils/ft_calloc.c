/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:52:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/19 02:40:44 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (size && nmemb > INT_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, (nmemb * size));
	return (ptr);
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int	main(void)
//{
//	const size_t	count = 10;
//	const size_t	size = sizeof(int);
//	int				*ptr;
//	size_t			i;
//
//	i = 0;
//	ptr = (int *)ft_calloc(count, size);
//	if (!ptr)
//	{
//		free(ptr);
//		return (1);
//	}
//	while (i < count)
//	{
//		if (ptr[i] != 0)
//		{
//			printf("\033[31m[ko] not zero at index %zu\033[0m\n", i);
//			break ;
//		}
//		i++;
//	}
//	printf("\033[32m[ok]\033[0m\n");
//	free(ptr);
//	return (0);
//}
