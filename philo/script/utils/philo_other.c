/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/05 11:21:13 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	time_to_ms(struct timeval time, t_philo_data *data)
{
	long	result;

	result = (time.tv_sec - data->start_time.tv_sec) * 1000
		+ (time.tv_usec - data->start_time.tv_usec) / 1000;
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

int	death_check(t_philo *philo)
{
	if ((time_to_ms(philo->data->cur_time, philo->data)
			- time_to_ms(philo->last_eat_time, philo->data))
		>= philo->data->ttdie)
		return (philo_set_status(philo, DEAD), 1);
	return (0);
}

void	philosleep(int ms, t_philo *philo)
{
	long	target;

	target = time_to_ms(philo->data->cur_time, philo->data) + ms;
	while (time_to_ms(philo->data->cur_time, philo->data) + 1 <= target
		&& !philo->data->is_finish)
	{
		if (philo->status == DEAD)
			break ;
		if (philo->status == EAT)
			gettimeofday(&philo->last_eat_time, NULL);
		death_check(philo);
	}
}
