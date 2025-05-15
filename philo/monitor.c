/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:44:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/15 15:55:02 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_check(t_philo *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if ((time_to_ms(philo->cur_time, philo->data->start)
			- time_to_ms(philo->last_eat, philo->data->start))
		> philo->data->ttdie)
	{
		pthread_mutex_lock(philo->data->write);
		if (philo->data->is_running == true && philo->data->can_write == true)
			printf(L_TIME L_P_DI"\n",
				time_to_ms(philo->cur_time, philo->data->start), philo->id + 1);
		philo->data->can_write = false;
		pthread_mutex_unlock(philo->data->write);
		pthread_mutex_lock(philo->data->monilock);
		philo->data->is_running = false;
		pthread_mutex_unlock(philo->data->monilock);
		return (true);
	}
	return (false);
}

void	monitor(t_phdata *data)
{
	int		i;

	i = 0;
	usleep(10 * ONE_MS);
	while (data->is_running)
	{
		death_check(data->philo[i]);
		pthread_mutex_lock(data->monilock);
		if (data->is_running == false || data->full_count >= data->n_philo)
		{
			data->is_running = false;
			if (PHILO_DEBUG)
				printf("ENDING BY MONITOR\n");
			pthread_mutex_unlock(data->monilock);
			pthread_mutex_lock(data->write);
			data->can_write = false;
			pthread_mutex_unlock(data->write);
			return ;
		}
		pthread_mutex_unlock(data->monilock);
		if (i >= data->n_philo - 1)
			i = 0;
		else
			i++;
	}
}
