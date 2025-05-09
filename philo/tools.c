/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:45:59 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/09 15:29:22 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wr_philo_msg(t_philo *philo, t_phdata *data, int status)
{
	if (status == SLEEP && data->is_running && !philo->is_full)
		printf(L_TIME L_P_SL"\n",
			time_to_ms(philo->last_update, data->start_time), philo->id);
	else if (status == THINK && data->is_running && !philo->is_full)
		printf(L_TIME L_P_TH"\n",
			time_to_ms(philo->last_update, data->start_time), philo->id);
	else if (status == TAKE_FORK && data->is_running && !philo->is_full)
		printf(L_TIME L_P_TF"\n",
			time_to_ms(philo->last_update, data->start_time), philo->id);
	else if (status == DEAD && data->is_running && !philo->is_full)
		printf(L_TIME L_P_DI"\n",
			time_to_ms(philo->last_update, data->start_time), philo->id);
	else if (status == EAT && data->is_running && !philo->is_full)
		printf(L_TIME L_P_EA"\n",
			time_to_ms(philo->last_update, data->start_time), philo->id);
}

void	philo_set_status(t_philo *philo, long status, t_phdata *data)
{
	gettimeofday(&philo->last_update, NULL);
	wr_philo_msg(philo, data, status);
	if (status != TAKE_FORK && philo->status != DEAD)
		philo->status = status;
	if (philo->status == DEAD || status == DEAD)
		philo->is_alive = false;
}
