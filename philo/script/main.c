/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:17:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/03/01 11:11:29 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

t_philo	*new_philo(t_philo_data *d)
{
	static long	i = 0;
	t_philo		*new;

	i++;
	new = ft_calloc(1, sizeof(t_philo));
	ft_lstadd_front(ft_alist(),
		ft_lstnew(new->l_fork = ft_calloc(1, sizeof(pthread_mutex_t))));
	if (new == NULL)
		return (NULL);
	new->data = d;
	new->id = i;
	pthread_create(&new->thread, NULL, (void *)philo_loop, (void *)new);
	pthread_mutex_init(new->l_fork, NULL);
	if (d->fork_c > 200)
	{
		printf(LANG_W LANG_W_TMP);
		usleep(ONE_S);
	}
	return (new);
}

void	data_free(t_philo_data *data)
{
	ft_lstclear(&(data->philo), free);
	ft_lstclear(ft_alist(), free);
}

static void	data_init(t_philo_data *data, char **av)
{
	static long	i = 0;

	data->philo_c = ft_atol(av[1]);
	data->fork_c = data->philo_c;
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	if (av[5] != NULL && av[5][0] != '\0')
		data->t_must_eat = ft_atol(av[5]);
	else
		data->t_must_eat = RETURN_ERROR;
	if (data->fork_c <= 0)
		return (ft_lstclear(ft_alist(), free), wr_error(LANG_E_IPA), exit (-1));
	while (++i <= data->fork_c)
		ft_lstadd_back(&data->philo, ft_lstnew(new_philo(data)));
	philo_lstiter_r_fork(data->philo);
	data->was_init = 1;
	gettimeofday(&data->start_time, NULL);
}

int	main(int ac, char **av)
{
	t_philo_data	*data;

	if (ac < 5 || ac > 6)
		return (wr_error(LANG_E_ARG), RETURN_ERROR);
	ft_lstadd_back(ft_alist(),
		ft_lstnew(data = ft_calloc(1, sizeof(t_philo_data))));
	gettimeofday(&data->start_time, NULL);
	data_init(data, av);
	while (data->philo_c > 0)
		gettimeofday(&data->cur_time, NULL);
	philo_lstiter_pthj(data->philo);
	if (PHILO_DEBUG)
		printf("\nFork Count = %ld\nTime to die = %ld\nTime to eat = %ld\nTime"
			" to sleep = %ld\nTime each Philo must eat = %ld\n", data->fork_c,
			data->ttdie, data->tteat, data->ttsleep, data->t_must_eat);
	data_free(data);
	return (RETURN_SUCCESS);
}
