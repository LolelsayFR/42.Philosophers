/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/01 21:28:30 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	time_to_ms(struct timeval time)
{
	long	result;

	result = (time.tv_usec / 1000) + (time.tv_sec * 1000);
	return (result);
}

t_philo	*get_philo(long id, t_philo_data *d)
{
	t_philo	*philo;
	t_list	*lst;

	lst = d->philo;
	if (!lst)
		return (NULL);
	if (id > d->fork_c)
		id = 1;
	if (id < 1)
		id = d->fork_c;
	while (lst)
	{
		philo = (t_philo *)lst->content;
		if (philo->id == id)
			return (philo);
		lst = lst->next;
	}
	return (NULL);
}

int	philo_mul_cond(int i, t_philo_data *d, t_philo *philo)
{
	(void)philo;
	if (i == 1 && d->fork_c == d->philo_c)
		return (1);
	return (0);
}
