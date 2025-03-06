/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/05 19:46:57 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_set_status(t_philo *philo, long status)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->status = status;
	pthread_mutex_lock(philo->data->mu_philo_c);
	wr_philo_msg(time, philo);
	if (status == DEAD)
		philo->data->philo_c--;
	pthread_mutex_unlock(philo->data->mu_philo_c);
}

void	philo_sleep(t_philo *philo)
{
	death_check(philo);
	philo_set_status(philo, SLEEP);
	philosleep(philo->data->ttsleep, philo);
	death_check(philo);
}

void	philo_think(t_philo *philo)
{
	death_check(philo);
	philo_set_status(philo, THINK);
	death_check(philo);
}

void	*philo_eat(t_philo *philo)
{
	if (philo->data->fork_c == 1)
		return (philosleep(philo->data->ttdie, philo), NULL);
	pthread_mutex_lock(philo->l_fork);
	death_check(philo);
	philo_set_status(philo, TAKE_FORK);
	pthread_mutex_lock(philo->r_fork);
	death_check(philo);
	philo_set_status(philo, TAKE_FORK);
	philo_set_status(philo, EAT);
	philo->meal++;
	gettimeofday(&philo->last_eat_time, NULL);
	philosleep(philo->data->tteat, philo);
	if (PHILO_DEBUG && philo->meal == philo->data->n_must_eat)
		printf("Philo number %ld is full after %ld meal\n",
			philo->id, philo->meal);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	*philo_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->data->was_init);
	pthread_mutex_unlock(philo->data->was_init);
	gettimeofday(&philo->last_eat_time, NULL);
	pthread_mutex_lock(philo->shield);
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->status != DEAD && philo->meal != philo->data->n_must_eat
		&& !philo->data->is_finish)
	{
		philo_eat(philo);
		if (philo->status == DEAD || philo->meal == philo->data->n_must_eat
			|| philo->data->is_finish)
			break ;
		philo_think(philo);
		if (philo->status == DEAD || philo->meal == philo->data->n_must_eat
			|| philo->data->is_finish)
			break ;
		philo_sleep(philo);
	}
	pthread_mutex_lock(philo->data->mu_philo_c);
	philo->data->full_count++;
	pthread_mutex_unlock(philo->data->mu_philo_c);
	pthread_mutex_unlock(philo->shield);
	return (philo);
}
