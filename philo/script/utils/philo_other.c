/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/26 21:25:17 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	time_to_ms(struct timeval current_time, struct timeval start_time)
{
	return ((current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}

int	death_check(t_philo *philo, t_philo_data *data)
{
	if ((time_to_ms(philo->cur_time, philo->start_time)
			- time_to_ms(philo->last_eat_time, philo->start_time))
		>= data->ttdie)
	{
		philo_set_status(philo, DEAD, data);
		return (1);
	}
	return (0);
}

void	philosleep(const int ms, t_philo *philo, t_philo_data *data)
{
	struct timeval	start;
	long			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		death_check(philo, data);
		gettimeofday(&philo->cur_time, NULL);
		elapsed = time_to_ms(philo->cur_time, start);
		if (elapsed >= ms || death_check(philo, data))
			break ;
		usleep(50);
	}
}

void	philo_set_status(t_philo *philo, long status, t_philo_data *data)
{
	pthread_mutex_lock(data->shield);
	if (philo->status == status)
	{
		pthread_mutex_unlock(data->shield);
		return ;
	}
	gettimeofday(&philo->cur_time, NULL);
	wr_philo_msg(philo, data, status);
	if (status != TAKE_FORK && philo->status != DEAD)
		philo->status = status;
	if (philo->status == DEAD || status == DEAD)
	{
		philo->isdead = 1;
		pthread_mutex_lock(data->philo_edit);
		data->is_finish = 1;
		pthread_mutex_unlock(data->philo_edit);
	}
	pthread_mutex_unlock(data->shield);
}
