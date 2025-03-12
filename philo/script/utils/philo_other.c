/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:17:50 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/12 01:32:32 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	time_to_ms(struct timeval time, t_philo *data)
{
	long	result;

	result = (time.tv_sec - data->start_time.tv_sec) * 1000
		+ (time.tv_usec - data->start_time.tv_usec) / 1000;
	return (result);
}

int	death_check(t_philo *philo, t_philo_data *data)
{
	gettimeofday(&philo->cur_time, NULL);
	if ((time_to_ms(philo->cur_time, philo)
			- time_to_ms(philo->last_eat_time, philo)) >= data->ttdie)
		return (philo_set_status(philo, DEAD, data), 1);
	return (0);
}

void	philosleep(const int ms, t_philo *philo, t_philo_data *data)
{
	long	target;

	target = time_to_ms(philo->cur_time, philo) + ms;
	while (time_to_ms(philo->cur_time, philo) < target
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
	if (philo->status == status)
		return ;
	gettimeofday(&philo->cur_time, NULL);
	if (status != TAKE_FORK && philo->status != DEAD)
		philo->status = status;
	if (philo->status == DEAD || status == DEAD)
		philo->isdead = 1;
	wr_philo_msg(philo, data, status);
}
