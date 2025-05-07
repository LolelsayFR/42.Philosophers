/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:18:28 by emaillet          #+#    #+#             */
/*   Updated: 2025/05/07 16:42:29 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	data_checker(t_phdata *data, char **av)
{
	if (av[5] != NULL && av[5][0] != '\0' && ft_atol(av[5]) > 0
		&& ft_atol(av[5]) < LONG_MAX)
		data->n_must_eat = ft_atol(av[5]);
	else
		data->n_must_eat = -1;
	if (data->n_philo <= 0 || data->n_philo > 200)
		return (ft_alist_free(), ft_putendl_fd(LANG_E_IPA, 2), false);
	if (data->ttdie <= 0 || data->ttdie > INT_MAX)
		return (ft_alist_free(), ft_putendl_fd(LANG_E_TTD, 2), false);
	if (data->tteat <= 0 || data->tteat > INT_MAX)
		return (ft_alist_free(), ft_putendl_fd(LANG_E_TTE, 2), false);
	if (data->ttsleep <= 0 || data->ttsleep > INT_MAX)
		return (ft_alist_free(), ft_putendl_fd(LANG_E_TTS, 2), false);
	return (1);
}

static pthread_mutex_t	**fork_tab_creator(int i)
{
	pthread_mutex_t	**result;

	ft_alist_add_back(result = ft_calloc(i, sizeof(pthread_mutex_t *)));
	i--;
	while (i >= 0)
	{
		ft_alist_add_back(result[i] = ft_calloc(1, sizeof(pthread_mutex_t)));
		pthread_mutex_init(result[i], NULL);
		i--;
	}
	return (result);
}

static void	philo_tab_launcher(int i, t_phdata *data)
{
	ft_alist_add_back(data->philo = ft_calloc(i, sizeof(t_philo *)));
	i--;
	while (i >= 0)
	{
		ft_alist_add_back(data->philo[i] = ft_calloc(1, sizeof(t_philo)));
		data->philo[i]->id = i;
		pthread_create(&data->philo[i]->thread,
			NULL, (void *)philo_loop, (void *)data->philo[i]);
		printf("Thread id %d is created\n", i);
		i--;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		printf("Thread id %d is join\n", i);
		i++;
	}
}

static bool	data_init(t_phdata *data, char **av)
{
	data->n_philo = ft_atol(av[1]);
	data->n_fork = data->n_philo;
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	data->phforks = fork_tab_creator(data->n_fork);
	if (data_checker(data, av) == false)
		return (false);
	gettimeofday(&data->start_time, NULL);
	data->was_init = true;
	return (true);
}

int	main(int ac, char **av)
{
	t_phdata	*data;

	if (ac < 5 || ac > 6)
		return (ft_putendl_fd(LANG_E_ARG, 2), RETURN_ERROR);
	data = get_data();
	if (data == NULL)
		return (ft_putendl_fd(LANG_E_MALLOC, 2), RETURN_ERROR);
	if (data_init(data, av) == false)
		return (RETURN_ERROR);
	philo_tab_launcher(data->n_philo, data);
	ft_alist_free();
	return (RETURN_SUCCESS);
}
