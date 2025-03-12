/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 07:33:51 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/12 05:31:05 by emaillet         ###   ########.fr       */
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

void	wr_philo_msg(t_philo *philo, t_philo_data *data, int status)
{
	int	is_sim_finished;

	pthread_mutex_lock(data->philo_edit);
	is_sim_finished = data->is_finish;
	pthread_mutex_unlock(data->philo_edit);
	if (is_sim_finished || philo->isdead || philo->isfull)
		return ;
	pthread_mutex_lock(data->wr_msg);
	if (status == SLEEP && !data->is_finish && !philo->isfull)
		printf(L_TIME L_P_SL"\n",
			time_to_ms(philo->cur_time, data->start_time), philo->id);
	else if (status == THINK && !data->is_finish && !philo->isfull)
		printf(L_TIME L_P_TH"\n",
			time_to_ms(philo->cur_time, data->start_time), philo->id);
	else if (status == TAKE_FORK && !data->is_finish && !philo->isfull)
		printf(L_TIME L_P_TF"\n",
			time_to_ms(philo->cur_time, data->start_time), philo->id);
	else if (status == DEAD && !data->is_finish && !philo->isfull)
		printf(L_TIME L_P_DI"\n",
			time_to_ms(philo->cur_time, data->start_time), philo->id);
	else if (status == EAT && !data->is_finish && !philo->isfull)
		printf(L_TIME L_P_EA"\n",
			time_to_ms(philo->cur_time, data->start_time), philo->id);
	pthread_mutex_unlock(data->wr_msg);
}
