/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/12 03:45:05 by emaillet         ###   ########.fr       */
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
	int	is_sim_finished;

	pthread_mutex_lock(data->philo_edit);
	is_sim_finished = data->is_finish;
	pthread_mutex_unlock(data->philo_edit);
	if (is_sim_finished)
		return (1);
	gettimeofday(&philo->cur_time, NULL);
	if ((time_to_ms(philo->cur_time, data->start_time)
			- time_to_ms(philo->last_eat_time, data->start_time))
		>= data->ttdie)
		return (philo_set_status(philo, DEAD, data), 1);
	return (0);
}

void	philosleep(const int ms, t_philo *philo, t_philo_data *data)
{
	long	target;

	target = time_to_ms(philo->cur_time, data->start_time) + ms;
	while (time_to_ms(philo->cur_time, data->start_time) < target
		&& philo->status != DEAD)
	{
		gettimeofday(&philo->cur_time, NULL);
		if (philo->status == EAT)
			gettimeofday(&philo->last_eat_time, NULL);
		death_check(philo, data);
		if (philo->status == DEAD)
			break ;
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
		philo->isdead = 1;
	pthread_mutex_unlock(data->shield);
}
