/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:45:59 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/12 11:25:20 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wr_philo_msg(t_philo *philo, t_phdata *data, int status)
{
	if (philo->is_alive == false)
		return ;
	pthread_mutex_lock(philo->set_status);
	pthread_mutex_lock(data->monilock);
	if (status == SLEEP && data->is_running && !philo->is_full)
		printf(L_TIME L_P_SL"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	else if (status == THINK && data->is_running && !philo->is_full)
		printf(L_TIME L_P_TH"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	else if (status == TAKE_FORK && data->is_running && !philo->is_full)
		printf(L_TIME L_P_TF"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	else if (status == EAT && data->is_running && !philo->is_full)
		printf(L_TIME L_P_EA"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	pthread_mutex_unlock(data->monilock);
	pthread_mutex_unlock(philo->set_status);
}

void	philo_set_status(t_philo *philo, int status, t_phdata *data)
{
	gettimeofday(&philo->cur_time, NULL);
	gettimeofday(&philo->last_update, NULL);
	wr_philo_msg(philo, data, status);
	if (status != TAKE_FORK && philo->status != DEAD)
	{
		pthread_mutex_lock(philo->set_status);
		philo->status = status;
		pthread_mutex_unlock(philo->set_status);
	}
	if (philo->status == DEAD || status == DEAD)
		philo->is_alive = false;
}

bool	death_check(t_philo *philo)
{
	gettimeofday(&philo->cur_time, NULL);
	if ((time_to_ms(philo->cur_time, philo->data->start)
			- time_to_ms(philo->last_eat, philo->data->start))
		>= philo->data->ttdie)
	{
		if (philo->status == DEAD)
			return (true);
		pthread_mutex_lock(philo->set_status);
		pthread_mutex_lock(philo->data->monilock);
		if (philo->data->is_running == true)
			printf(L_TIME L_P_DI"\n",
				time_to_ms(philo->cur_time, philo->data->start), philo->id + 1);
		pthread_mutex_unlock(philo->data->monilock);
		philo->status = DEAD;
		philo->is_alive = false;
		pthread_mutex_unlock(philo->set_status);
		return (true);
	}
	return (false);
}
