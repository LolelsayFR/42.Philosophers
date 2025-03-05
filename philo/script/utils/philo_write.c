/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 07:33:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/05 10:33:44 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	wr_error(char *str)
{
	int		i;

	write(2, LANG_E, ft_strlen(LANG_E));
	i = 1;
	while (str[i] != '\0')
		i++;
	write(2, str, i);
}

void	wr_philo_msg(struct timeval time, t_philo *philo)
{
	if (philo->status == SLEEP
		&& philo->data->philo_c > 1 && !philo->data->is_finish)
		printf(L_TIME L_P_SL"\n", time_to_ms(time, philo->data), philo->id);
	else if (philo->status == THINK
		&& philo->data->philo_c > 1 && !philo->data->is_finish)
		printf(L_TIME L_P_TH"\n", time_to_ms(time, philo->data), philo->id);
	else if (philo->status == TAKE_FORK
		&& philo->data->philo_c > 1 && !philo->data->is_finish)
		printf(L_TIME L_P_TF"\n", time_to_ms(time, philo->data), philo->id);
	else if (philo->status == DEAD && !philo->data->is_finish
		&& philo->data->philo_c == philo->data->fork_c)
		printf(L_TIME L_P_DI"\n", time_to_ms(time, philo->data), philo->id);
	else if (philo->status == EAT && (philo->meal > philo->data->n_must_eat
			|| philo->data->n_must_eat != -1) && philo->data->philo_c > 1
		&& !philo->data->is_finish)
		printf(L_TIME L_P_EA"\n", time_to_ms(time, philo->data), philo->id);
}
