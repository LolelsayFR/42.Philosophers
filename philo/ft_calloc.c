/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:52:01 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/06 09:37:27 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
