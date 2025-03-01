/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 07:33:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/01 09:26:11 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/types/struct_timeval.h>

void	wr_error(char *str)
{
	int		i;

	write(2, LANG_E, 29);
	i = 1;
	while (str[i] != '\0')
		i++;
	write(2, str, i);
}

void	wr_philo_msg(struct timeval time, t_philo *philo)
{
	if (philo->status == SLEEP)
		printf(L_TIME L_P_SL"\n", (time.tv_sec - philo->data->start_time.tv_sec)
			/ 3600, (time.tv_sec - philo->data->start_time.tv_sec) / 60,
			(time.tv_sec - philo->data->start_time.tv_sec) % 60,
			time.tv_usec / 1000, philo->id);
	else if (philo->status == THINK)
		printf(L_TIME L_P_TH"\n", (time.tv_sec - philo->data->start_time.tv_sec)
			/ 3600, (time.tv_sec - philo->data->start_time.tv_sec) / 60,
			(time.tv_sec - philo->data->start_time.tv_sec) % 60,
			time.tv_usec / 1000, philo->id);
	else if (philo->status == TAKE_FORK)
		printf(L_TIME L_P_TF"\n", (time.tv_sec - philo->data->start_time.tv_sec)
			/ 3600, (time.tv_sec - philo->data->start_time.tv_sec) / 60,
			(time.tv_sec - philo->data->start_time.tv_sec) % 60,
			time.tv_usec / 1000, philo->id);
	else if (philo->status == DEAD)
		printf(L_TIME L_P_DI"\n", (time.tv_sec - philo->data->start_time.tv_sec)
			/ 3600, (time.tv_sec - philo->data->start_time.tv_sec) / 60,
			(time.tv_sec - philo->data->start_time.tv_sec) % 60,
			time.tv_usec / 1000, philo->id);
	else if (philo->status == EAT)
		printf(L_TIME L_P_EA"\n", (time.tv_sec - philo->data->start_time.tv_sec)
			/ 3600, (time.tv_sec - philo->data->start_time.tv_sec) / 60,
			(time.tv_sec - philo->data->start_time.tv_sec) % 60,
			time.tv_usec / 1000, philo->id);
}
