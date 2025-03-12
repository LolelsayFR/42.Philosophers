/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:04:14 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/16 06:28:54 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_list	**ft_alist(void)
{
	static t_list	*alloc = NULL;

	if (alloc == NULL)
		alloc = ft_calloc(1, sizeof(t_list));
	return (&alloc);
}

static void	nufree(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_alist_free(void)
{
	t_list	**lst;

	lst = ft_alist();
	ft_lstclear(lst, nufree);
}
