/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:08:25 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/20 00:56:44 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_lang.h"

t_philo	*new_philo(t_philo_data *d, t_list *philo)
{
	static long	i = 0;
	t_philargs	*arg;

	i++;
	ft_lstadd_front(ft_alist(),
		ft_lstnew(arg = ft_calloc(1, sizeof(t_philargs))));
	arg->data = d;
	arg->philo = ft_calloc(1, sizeof(t_philo));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(arg->philo->l_fork = ft_calloc(1, sizeof(pthread_mutex_t))));
	if (arg->philo == NULL || arg->philo->l_fork == NULL)
		return (wr_error(LANG_E_MALLOC), data_free(d, philo), NULL);
	if (arg->philo == NULL)
		return (NULL);
	arg->philo->id = i;
	pthread_mutex_init(arg->philo->l_fork, NULL);
	pthread_create(&arg->philo->thread, NULL, (void *)philo_loop, (void *)arg);
	if (PHILO_DEBUG)
		printf(GRN"Philo thread %ld is created"RES, arg->philo->id);
	return (arg->philo);
}

void	data_free(t_philo_data *data, t_list *philo)
{
	pthread_mutex_lock(data->philo_edit);
	pthread_mutex_lock(data->wr_msg);
	data->is_finish = 1;
	pthread_mutex_unlock(data->philo_edit);
	pthread_mutex_unlock(data->wr_msg);
	usleep(ONE_MS * 10);
	philo_lstiter_pthj(philo);
	if (PHILO_DEBUG)
		printf("\nFork Count = %ld\nTime to die = %ld\nTime to eat = %ld\nTime"
			" to sleep = %ld\nTime each Philo must eat = %ld\n", data->fork_c,
			data->ttdie, data->tteat, data->ttsleep, data->n_must_eat);
	ft_lstclear(&philo, free);
	ft_lstclear(ft_alist(), free);
}

static int	data_checker(t_philo_data *data, char **av)
{
	if (av[5] != NULL && av[5][0] != '\0' && ft_atol(av[5]) > 0
		&& ft_atol(av[5]) < LONG_MAX)
		data->n_must_eat = ft_atol(av[5]);
	else
		data->n_must_eat = -1;
	if (data->philo_c <= 0 || data->philo_c > 200)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_IPA), -1);
	if (data->ttdie <= 0 || data->ttdie > INT_MAX)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTD), -1);
	if (data->tteat <= 0 || data->tteat > INT_MAX)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTE), -1);
	if (data->ttsleep <= 0 || data->ttsleep > INT_MAX)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_TTS), -1);
	return (1);
}

static int	data_init(t_philo_data *data, char **av, t_list **philo)
{
	static long	i = 0;

	pthread_mutex_init(data->shield, NULL);
	pthread_mutex_init(data->philo_edit, NULL);
	pthread_mutex_init(data->wr_msg, NULL);
	pthread_mutex_lock(data->philo_edit);
	data->philo_c = ft_atol(av[1]);
	data->fork_c = data->philo_c;
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	if (data_checker(data, av) == -1)
		return (-1);
	while (++i <= data->fork_c)
		ft_lstadd_front(philo, ft_lstnew(new_philo(data, *philo)));
	if (data->fork_c > 1)
		philo_lstiter_r_fork(*philo, data);
	while (data->start_time.tv_usec > 200 || data->start_time.tv_usec < 50)
		gettimeofday(&data->start_time, NULL);
	data->was_init = 1;
	pthread_mutex_unlock(data->philo_edit);
	while (philo_lstiter_end(*philo, data))
		philo_lstiter_end(*philo, data);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo_data	*data;
	t_list			*philo;

	if (ac < 5 || ac > 6)
		return (wr_error(LANG_E_ARG), RETURN_ERROR);
	ft_lstadd_back(ft_alist(),
		ft_lstnew(data = ft_calloc(1, sizeof(t_philo_data))));
	ft_lstadd_back(ft_alist(),
		ft_lstnew(data->philo_edit = ft_calloc(1, sizeof(pthread_mutex_t))));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(data->shield = ft_calloc(1, sizeof(pthread_mutex_t))));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(data->wr_msg = ft_calloc(1, sizeof(pthread_mutex_t))));
	philo = NULL;
	if (data == NULL || data->philo_edit == NULL || data->shield == NULL
		|| data->wr_msg == NULL)
		return (wr_error(LANG_E_MALLOC), RETURN_ERROR);
	if (data_init(data, av, &philo) == -1)
		return (RETURN_ERROR);
	if (PHILO_DEBUG)
		printf(YEL"MAIN LOOP FINISHED"RES);
	data_free(data, philo);
	return (RETURN_SUCCESS);
}
