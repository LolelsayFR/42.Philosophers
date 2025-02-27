/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:40:35 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/27 08:14:00 by emaillet         ###   ########.fr       */
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
		if (PHILO_DEBUG)
			printf(RED"Philo %ld was ended\n"RES, philo->id);
		pthread_join(philo->thread, NULL);
		lst = lst->next;
	}
}
