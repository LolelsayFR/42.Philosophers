/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:07:57 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/12 09:22:28 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_to_ms(struct timeval current_time, struct timeval start_time)
{
	return (((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000))
		- ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000)));
}

void	ms_sleep(const int ms, t_philo *philo)
{
	long	elapsed;

	while (1)
	{
		gettimeofday(&philo->cur_time, NULL);
		elapsed = time_to_ms(philo->cur_time, philo->last_update);
		if (elapsed >= ms || death_check(philo))
			break ;
		usleep(50);
	}
}
