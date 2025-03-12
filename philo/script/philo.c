/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/12 03:32:10 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo, t_philo_data *data)
{
	death_check(philo, data);
	philo_set_status(philo, SLEEP, data);
	philosleep(data->ttsleep, philo, data);
	death_check(philo, data);
}

void	philo_think(t_philo *philo, t_philo_data *data)
{
	death_check(philo, data);
	philo_set_status(philo, THINK, data);
	death_check(philo, data);
}

static void	philo_take_fork(t_philo *philo, t_philo_data *data)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		philo_set_status(philo, TAKE_FORK, data);
		pthread_mutex_lock(philo->r_fork);
		philo_set_status(philo, TAKE_FORK, data);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		philo_set_status(philo, TAKE_FORK, data);
		pthread_mutex_lock(philo->l_fork);
		philo_set_status(philo, TAKE_FORK, data);
	}
}

void	*philo_eat(t_philo *philo, t_philo_data *data)
{
	if (data->fork_c == 1)
		return (philosleep(data->ttdie, philo, data), NULL);
	philo_take_fork(philo, data);
	philo_set_status(philo, EAT, data);
	pthread_mutex_lock(data->philo_edit);
	philo->meal++;
	if (philo->meal == data->n_must_eat)
		philo->isfull = 1;
	pthread_mutex_unlock(data->philo_edit);
	gettimeofday(&philo->last_eat_time, NULL);
	philosleep(data->tteat, philo, data);
	if (PHILO_DEBUG && philo->meal == data->n_must_eat)
		printf("Philo number %ld is full after %ld meal\n",
			philo->id, philo->meal);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

void	*philo_loop(t_philargs *arg)
{
	pthread_mutex_lock(arg->data->philo_edit);
	pthread_mutex_unlock(arg->data->philo_edit);
	gettimeofday(&arg->philo->cur_time, NULL);
	gettimeofday(&arg->philo->last_eat_time, NULL);
	while (!arg->data->is_finish && !death_check(arg->philo, arg->data))
	{
		philo_eat(arg->philo, arg->data);
		if (arg->data->is_finish || death_check(arg->philo, arg->data))
			break ;
		philo_think(arg->philo, arg->data);
		if (arg->data->is_finish || death_check(arg->philo, arg->data))
			break ;
		philo_sleep(arg->philo, arg->data);
	}
	return (arg);
}
