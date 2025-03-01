/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/01 21:08:26 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_set_status(t_philo *philo, long status)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->status = status;
	if (philo_mul_cond(1, philo->data, philo))
		wr_philo_msg(time, philo);
	pthread_mutex_lock(philo->data->mu_philo_c);
	if (status == DEAD || (philo->meal > philo->data->n_must_eat
			&& philo->data->n_must_eat != -1))
		philo->data->philo_c--;
	pthread_mutex_unlock(philo->data->mu_philo_c);
}

void	philo_sleep(t_philo *philo)
{
	if ((time_to_ms(philo->data->cur_time)
			- time_to_ms(philo->last_eat_time)) >= philo->data->ttdie)
		philo_set_status(philo, DEAD);
	philo_set_status(philo, SLEEP);
	usleep(philo->data->ttsleep * 1000);
	if ((time_to_ms(philo->data->cur_time)
			- time_to_ms(philo->last_eat_time)) >= philo->data->ttdie)
		philo_set_status(philo, DEAD);
}

void	philo_think(t_philo *philo)
{
	philo_set_status(philo, THINK);
	while (get_philo(philo->id + 1, philo->data)->fork_count > 0
		&& get_philo(philo->id - 1, philo->data)->fork_count > 0
		&& get_philo(philo->id + 1, philo->data)->starve > philo->starve
		&& get_philo(philo->id - 1, philo->data)->starve > philo->starve)
		usleep(1000);
	if ((time_to_ms(philo->data->cur_time)
			- time_to_ms(philo->last_eat_time)) >= philo->data->ttdie)
		philo_set_status(philo, DEAD);
}

void	*philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo_set_status(philo, TAKE_FORK);
	philo->fork_count++;
	if (get_philo(philo->id + 1, philo->data)->fork_count > 0
		&& get_philo(philo->id - 1, philo->data)->fork_count > 0)
		return (pthread_mutex_unlock(philo->l_fork), philo->fork_count--, NULL);
	pthread_mutex_lock(philo->r_fork);
	philo_set_status(philo, TAKE_FORK);
	philo->fork_count++;
	philo_set_status(philo, EAT);
	usleep(philo->data->tteat * 1000);
	philo->meal++;
	gettimeofday(&philo->last_eat_time, NULL);
	pthread_mutex_unlock(philo->r_fork);
	philo->fork_count--;
	pthread_mutex_unlock(philo->l_fork);
	philo->fork_count--;
	if (PHILO_DEBUG && (philo->data->n_must_eat > 0
			&& philo->meal >= philo->data->n_must_eat))
		printf("Philo number %ld is full after %ld meal\n",
			philo->id, philo->meal);
	return (NULL);
}

void	*philo_loop(t_philo *philo)
{
	while (philo->data->was_init == 0)
		usleep(500);
	gettimeofday(&philo->last_eat_time, NULL);
	while (philo->status != DEAD && philo->data->philo_c == philo->data->fork_c)
	{
		if (philo->data->philo_c > 1)
		{
			philo_eat(philo);
			if (philo->status == DEAD || !philo_mul_cond(1, philo->data, philo))
				break ;
			philo_think(philo);
			if (philo->status == DEAD || !philo_mul_cond(1, philo->data, philo))
				break ;
			philo_sleep(philo);
		}
		else if ((time_to_ms(philo->data->cur_time)
				- time_to_ms(philo->last_eat_time)) >= philo->data->ttdie)
			philo_set_status(philo, DEAD);
	}
	if (PHILO_DEBUG && philo->status == DEAD)
		printf("Philo number %ld is dead (%i%% starving after %ld meal)\n",
			philo->id, philo->starve, philo->meal);
	return (philo);
}
