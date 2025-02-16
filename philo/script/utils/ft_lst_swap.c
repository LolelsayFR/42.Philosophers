/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:21:52 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/20 16:28:39 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lst_swap(t_list **a, t_list **b)
{
	void	*tmp;

	if (!a || !b)
		return ;
	tmp = (*a)->content;
	(*a)->content = (*b)->content;
	(*b)->content = tmp;
}
