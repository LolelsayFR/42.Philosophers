/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/12 23:47:03 by emaillet         ###   ########.fr       */
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
	(void)data;
	(void)philo;
}

void	*philo_eat(t_philo *philo, t_philo_data *data)
{
	if (data->fork_c == 1)
		return (philosleep(data->ttdie, philo, data), NULL);
	philo_take_fork(philo, data);
	philo_set_status(philo, EAT, data);
	sem_wait(data->shield);
	philo->meal++;
	if (philo->meal == data->n_must_eat)
		philo->isfull = 1;
	sem_post(data->shield);
	gettimeofday(&philo->last_eat_time, NULL);
	philosleep(data->tteat, philo, data);
	if (PHILO_DEBUG && philo->meal == data->n_must_eat)
		printf("Philo number %ld is full after %ld meal\n",
			philo->id, philo->meal);
	return (NULL);
}

void	*philo_loop(t_philargs *arg)
{
	long	is_sim_finished;

	sem_wait(arg->data->philo_edit);
	sem_post(arg->data->philo_edit);
	gettimeofday(&arg->philo->cur_time, NULL);
	gettimeofday(&arg->philo->last_eat_time, NULL);
	is_sim_finished = 0;
	if (PHILO_DEBUG)
		printf(GRN"Philo Enter Loop %ld is created"RES, arg->philo->id);
	while (!is_sim_finished || !arg->philo->isdead || !arg->philo->isfull)
	{
		sem_wait(arg->data->philo_edit);
		is_sim_finished = arg->data->is_finish;
		sem_post(arg->data->philo_edit);
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
