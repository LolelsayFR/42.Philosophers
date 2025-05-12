/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:44:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/12 11:10:54 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_all_full(t_phdata *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(data->philo[i]->set_status);
		if (data->philo[i]->is_full == false)
		{
			pthread_mutex_unlock(data->philo[i]->set_status);
			return (false);
		}
		pthread_mutex_unlock(data->philo[i]->set_status);
		i++;
	}
	return (true);
}

void	monitor(t_phdata *data)
{
	int		i;
	bool	all_full;

	i = 0;
	all_full = is_all_full(data);
	while (data->is_running)
	{
		pthread_mutex_lock(data->philo[i]->set_status);
		if (data->philo[i]->is_alive == false || all_full == true)
		{
			pthread_mutex_lock(data->monilock);
			data->is_running = false;
			pthread_mutex_unlock(data->monilock);
			pthread_mutex_unlock(data->philo[i]->set_status);
			return ;
		}
		pthread_mutex_unlock(data->philo[i]->set_status);
		if (i >= data->n_philo - 1)
		{
			all_full = is_all_full(data);
			i = 0;
		}
		else
			i++;
	}
}
