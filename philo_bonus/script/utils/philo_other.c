/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/13 00:16:57 by emaillet         ###   ########.fr       */
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

	is_sim_finished = data->is_finish;
	if (is_sim_finished)
		return (1);
	gettimeofday(&philo->cur_time, NULL);
	if ((time_to_ms(philo->cur_time, data->start_time)
			- time_to_ms(philo->last_eat_time, data->start_time))
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
	struct timeval	now;
	long			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&philo->cur_time, NULL);
		death_check(philo, data);
		gettimeofday(&now, NULL);
		elapsed = time_to_ms(now, start);
		if (elapsed >= ms || death_check(philo, data))
			break ;
		usleep(50);
	}
}

void	philo_set_status(t_philo *philo, long status, t_philo_data *data)
{
	if (philo->status == status)
	{
		return ;
	}
	gettimeofday(&philo->cur_time, NULL);
	wr_philo_msg(philo, data, status);
	if (status != TAKE_FORK && philo->status != DEAD)
		philo->status = status;
	if (philo->status == DEAD || status == DEAD)
	{
		philo->isdead = 1;
		data->is_finish = 1;
	}
}
