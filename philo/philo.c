/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:12:47 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/16 14:54:31 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo, t_phdata *data)
{
	philo_set_status(philo, SLEEP, data);
	ms_sleep(data->ttsleep, philo);
}

static void	philo_think(t_philo *philo, t_phdata *data)
{
	philo_set_status(philo, THINK, data);
}

static void	philo_take_fork(t_philo *philo, t_phdata *data)
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;

	if (philo->id % 2 == 1)
	{
		right = data->phforks[philo->id];
		left = data->phforks[philo->id_next_fork];
	}
	else
	{
		left = data->phforks[philo->id];
		right = data->phforks[philo->id_next_fork];
	}
	pthread_mutex_lock(left);
	philo_set_status(philo, TAKE_FORK, data);
	if (philo->is_alive == false || data->n_fork == 1)
	{
		pthread_mutex_unlock(left);
		return ;
	}
	pthread_mutex_lock(right);
	philo_set_status(philo, TAKE_FORK, data);
}

static void	*philo_eat(t_philo *philo, t_phdata *data)
{
	philo_take_fork(philo, data);
	if (data->n_fork == 1)
		return (ms_sleep(data->ttdie + 1, philo), NULL);
	if (philo->is_alive == false)
		return (NULL);
	philo_set_status(philo, EAT, data);
	philo->n_meal++;
	if (philo->n_meal >= data->n_must_eat && data->n_must_eat != -1)
	{
		pthread_mutex_lock(philo->set_status);
		pthread_mutex_unlock(philo->set_status);
		pthread_mutex_lock(philo->data->monilock);
		if (philo->n_meal == data->n_must_eat)
			philo->data->full_count++;
		pthread_mutex_unlock(philo->data->monilock);
	}
	gettimeofday(&philo->last_eat, NULL);
	ms_sleep(data->tteat, philo);
	if (PHILO_DEBUG && philo->n_meal == data->n_must_eat)
		printf("Philo %d is full\n", philo->id + 1);
	pthread_mutex_unlock(data->phforks[philo->id]);
	pthread_mutex_unlock(data->phforks[philo->id_next_fork]);
	return (NULL);
}

void	*philo_loop(t_philo *philo)
{
	if (PHILO_DEBUG)
		printf("Philo %d enter the routine\n", philo->id + 1);
	gettimeofday(&philo->last_eat, NULL);
	gettimeofday(&philo->last_update, NULL);
	gettimeofday(&philo->start, NULL);
	if (philo->id == philo->data->n_fork - 1)
		philo->id_next_fork = 0;
	else
		philo->id_next_fork = philo->id + 1;
	pthread_mutex_lock(philo->data->monilock);
	while (philo->is_alive && philo->data->is_running)
	{
		pthread_mutex_unlock(philo->data->monilock);
		philo_eat(philo, philo->data);
		pthread_mutex_lock(philo->data->monilock);
		if (!philo->is_alive || !philo->data->is_running
			|| philo->data->n_fork == 1)
			break ;
		pthread_mutex_unlock(philo->data->monilock);
		philo_sleep(philo, philo->data);
		philo_think(philo, philo->data);
		pthread_mutex_lock(philo->data->monilock);
	}
	pthread_mutex_unlock(philo->data->monilock);
	return (NULL);
}
