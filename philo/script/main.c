/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 03:17:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/02/26 01:42:04 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(t_philo_data *d)
{
	static long	i = 0;
	t_philo		*new;

	i++;
	new = ft_calloc(1, sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->data = d;
	new->id = i;
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

	data->fork = ft_atol(av[1]);
	if (data->fork <= 0)
		return (ft_lstclear(ft_alist(), free), );
	data->ttdie = ft_atol(av[2]);
	data->tteat = ft_atol(av[3]);
	data->ttsleep = ft_atol(av[4]);
	if (av[5] != NULL && av[5][0] != '\0')
		data->t_must_eat = ft_atol(av[5]);
	else
		data->t_must_eat = RETURN_ERROR;
	while (++i <= data->fork)
		ft_lstadd_back(&data->philo, ft_lstnew(new_philo(data)));
}

int	philo_loop(t_philo_data *data)
{
	printf("Philo Count = %ld\n", data->loop_count + 1);
	data->loop_count++;
	if (data->loop_count == ft_lstsize(data->philo))
		return (-1);
	return (1);
}

int	main(int ac, char **av)
{
	t_philo_data	*data;

	if (ac < 5 || ac > 6)
		return (printf(RED"[ERROR] Invalid args\n"RES));
	ft_lstadd_back(ft_alist(),
		ft_lstnew(data = ft_calloc(1, sizeof(t_philo_data))));
	data_init(data, av);
	if (PHILO_DEBUG)
		printf(YEL"Fork Count = %ld\nTime to die = %ld\nTime to eat = %ld\nTime"
			"to sleep = %ld\nTime each Philo must eat = %ld\n"RES, data->fork,
			data->ttdie, data->tteat, data->ttsleep, data->t_must_eat);
	while (philo_loop(data) > 0)
		gettimeofday(&data->cur_time, NULL);
	data_free(data);
	return (RETURN_SUCCESS);
}
