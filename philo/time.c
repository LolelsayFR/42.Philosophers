/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:07:57 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/09 15:10:33 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_to_ms(struct timeval current_time, struct timeval start_time)
{
	return ((current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}

bool	death_check(t_philo *philo)
{

	gettimeofday(&philo->last_update, NULL);
	if ((time_to_ms(philo->last_update, philo->data->start_time)
			- time_to_ms(philo->last_eat, philo->data->start_time))
		>= philo->data->ttdie)
	{
		philo->status = DEAD;
		return (true);
	}
	return (false);
}

void	ms_sleep(const int ms, t_philo *philo)
{
	struct timeval	start;
	long			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&philo->last_update, NULL);
		death_check(philo);
		elapsed = time_to_ms(philo->last_update, start);
		if (elapsed >= ms || death_check(philo))
			break ;
		usleep(50);
	}
}
