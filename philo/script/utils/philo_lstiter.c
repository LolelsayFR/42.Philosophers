/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:40:35 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/01 09:27:09 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_lstiter_pthj(t_list *lst)
{
	t_philo	*philo;

	if (!lst)
		return ;
	while (lst)
	{
		philo = (t_philo *)lst->content;
		pthread_join(philo->thread, NULL);
		lst = lst->next;
	}
}

void	philo_lstiter_r_fork(t_list *lst_head)
{
	t_philo	*philo;
	t_philo	*philo_n;
	t_list	*lst;

	lst = lst_head;
	if (!lst)
		return ;
	while (lst)
	{
		philo = (t_philo *)lst->content;
		if (lst->next != NULL)
			philo_n = (t_philo *)lst->next->content;
		else
			philo_n = (t_philo *)lst_head->content;
		philo->r_fork = philo_n->l_fork;
		lst = lst->next;
	}
}
