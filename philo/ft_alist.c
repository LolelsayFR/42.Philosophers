/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:04:14 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/07 16:42:21 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	**ft_alist(void)
{
	static t_list	*alloc = NULL;

	if (alloc == NULL)
		alloc = ft_calloc(1, sizeof(t_list));
	return (&alloc);
}

t_phdata	*get_data(void)
{
	static t_phdata	*data = NULL;

	if (data == NULL)
		ft_alist_add_back(data = ft_calloc(1, sizeof(t_phdata)));
	return (data);
}

void	ft_alist_free(void)
{
	t_list	**lst;

	lst = ft_alist();
	ft_lstclear(lst, free);
}

void	ft_alist_add_back(void *content)
{
	ft_lstadd_back(ft_alist(), ft_lstnew(content));
}
