/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/13 00:38:00 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <semaphore.h>

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
	sem_wait(data->fork_sem);
	philo_set_status(philo, TAKE_FORK, data);
	usleep(50);
	sem_wait(data->fork_sem);
	philo_set_status(philo, TAKE_FORK, data);
}

void	*philo_eat(t_philo *philo, t_philo_data *data)
{
	if (data->fork_c == 1)
		return (philosleep(data->ttdie, philo, data), NULL);
	philo_take_fork(philo, data);
	philo_set_status(philo, EAT, data);
	philo->meal++;
	if (philo->meal == data->n_must_eat)
		philo->isfull = 1;
	gettimeofday(&philo->last_eat_time, NULL);
	philosleep(data->tteat, philo, data);
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
	if (PHILO_DEBUG && philo->meal == data->n_must_eat)
		printf("Philo number %ld is full after %ld meal\n",
			philo->id, philo->meal);
	return (NULL);
}

void	*philo_loop(t_philargs *arg)
{
	long	is_sim_finished;

	sem_wait(arg->data->start);
	sem_post(arg->data->start);
	gettimeofday(&arg->philo->cur_time, NULL);
	gettimeofday(&arg->philo->last_eat_time, NULL);
	is_sim_finished = 0;
	while (!is_sim_finished || !arg->philo->isdead || !arg->philo->isfull)
	{
		is_sim_finished = arg->data->is_finish;
		philo_eat(arg->philo, arg->data);
		if (arg->philo->isdead || arg->philo->isfull || is_sim_finished)
			break ;
		philo_think(arg->philo, arg->data);
		if (arg->philo->isdead || arg->philo->isfull || is_sim_finished)
			break ;
		philo_sleep(arg->philo, arg->data);
	}
	return (arg);
}
