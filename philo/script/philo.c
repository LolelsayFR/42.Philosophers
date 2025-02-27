/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 07:31:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/27 08:01:14 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(void *philo)
{
	t_philo	*data;

	data = (t_philo *)philo;
	printf("Philo %ld is thinking\n", data->id);
	sleep(2);
	printf("Philo %ld stop thinking\n", data->id);
	return (data);
}
