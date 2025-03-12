/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:40:35 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/13 00:39:43 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_lstiter_killall(t_list *lst)
{
	t_philo	*philo;

	while (lst)
	{
		philo = (t_philo *)lst->content;
		if (PHILO_DEBUG)
			printf(RED"Philo thread %ld is join"RES, philo->id);
		lst = lst->next;
	}
}

int	philo_lstiter_end(t_list *lst_head, t_philo_data *data)
{
	t_philo	*philo;
	t_list	*lst;
	int		full_count;

	full_count = 0;
	lst = lst_head;
	while (lst)
	{
		philo = lst->content;
		sem_wait(data->philo_edit);
		if (philo->isdead == 1)
		{
			sem_post(data->philo_edit);
			return (0);
		}
		if (!philo->isfull)
			full_count = 1;
		sem_post(data->philo_edit);
		lst = lst->next;
	}
	return (full_count);
}
