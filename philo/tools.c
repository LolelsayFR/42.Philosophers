/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:45:59 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/15 15:35:19 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wr_philo_msg(t_philo *philo, t_phdata *data, int status)
{
	(void)data;
	pthread_mutex_unlock(philo->data->write);
	if (philo->is_alive == false)
		return ;
	if (status == SLEEP)
		printf(L_TIME L_P_SL"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	else if (status == THINK)
		printf(L_TIME L_P_TH"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	else if (status == TAKE_FORK)
		printf(L_TIME L_P_TF"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
	else if (status == EAT)
		printf(L_TIME L_P_EA"\n",
			time_to_ms(philo->last_update, philo->data->start), philo->id + 1);
}

void	philo_set_status(t_philo *philo, int status, t_phdata *data)
{
	pthread_mutex_lock(philo->data->monilock);
	gettimeofday(&philo->cur_time, NULL);
	gettimeofday(&philo->last_update, NULL);
	pthread_mutex_lock(philo->data->write);
	if (philo->data->can_write == true)
		wr_philo_msg(philo, data, status);
	else
		pthread_mutex_unlock(philo->data->write);
	if (status != TAKE_FORK)
	{
		pthread_mutex_lock(philo->set_status);
		philo->status = status;
		pthread_mutex_unlock(philo->set_status);
	}
	pthread_mutex_unlock(philo->data->monilock);
}
