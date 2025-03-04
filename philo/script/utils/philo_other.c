/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/04 08:32:54 by emaillet         ###   ########.fr       */
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
	if (i == 1 && d->fork_c == d->philo_c)
		return (1);
	else if (i == 2 && philo->meal >= philo->data->n_must_eat
		&& philo->data->n_must_eat != -1)
		return (1);
	return (0);
}

int	death_check(t_philo *philo)
{
	if ((time_to_ms(philo->data->cur_time)
			- time_to_ms(philo->last_eat_time)) >= philo->data->ttdie)
		return (philo_set_status(philo, DEAD), 1);
	return (0);
}

void	philosleep(int ms, t_philo *philo)
{
	ms *= 10;
	while (ms > 0)
	{
		if (philo->status == DEAD)
			break ;
		usleep(ONE_MS / 10);
		ms--;
		if (philo->status != EAT)
			death_check(philo);
	}
}
