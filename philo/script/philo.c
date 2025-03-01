/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/01 11:11:56 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_set_status(t_philo *philo, long status)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->status = status;
	wr_philo_msg(time, philo);
	if (status == DEAD)
		philo->data->philo_c--;
}

void	*philo_loop(t_philo *philo)
{
	while (philo->data->was_init == 0)
		usleep(50);
	philo_set_status(philo, DEAD);
	return (philo);
}
