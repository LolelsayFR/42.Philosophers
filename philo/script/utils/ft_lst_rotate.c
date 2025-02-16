/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:46:11 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/20 16:17:58 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include <stddef.h>

t_list	*ft_lst_rotate(t_list **lst, size_t n)
{
	t_list	*tmp;
	t_list	*new_head;
	t_list	*new_tail;

	if (!*lst || !(*lst)->next)
		return (*lst);
	tmp = *lst;
	while (n-- > 1)
		tmp = tmp->next;
	new_head = tmp->next;
	new_tail = tmp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *lst;
	new_tail->next = NULL;
	*lst = new_head;
	return (*lst);
}

t_list	*ft_lst_unrotate(t_list **lst, size_t n)
{
	t_list	*tmp;

	if (!*lst || !(*lst)->next)
		return (*lst);
	while (n)
	{
		tmp = *lst;
		while (tmp->next->next)
			tmp = tmp->next;
		ft_lstadd_front(lst, tmp->next);
		tmp->next = NULL;
		n--;
	}
	return (*lst);
}
