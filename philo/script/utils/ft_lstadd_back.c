/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:28:20 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/20 03:39:34 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_lstadd_back(t_list **lst, t_list *lnew)
{
	t_list	*to_end;

	if (!lst || !lnew)
		return ;
	if (!*lst)
	{
		*lst = lnew;
		return ;
	}
	to_end = ft_lstlast(*lst);
	to_end->next = lnew;
}
