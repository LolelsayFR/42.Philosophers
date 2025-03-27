/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:29:03 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/27 15:54:57 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*dst;

	dst = ft_calloc(1, sizeof(t_list));
	if (!dst)
		return (NULL);
	dst -> content = content;
	dst -> next = NULL;
	return (dst);
}
