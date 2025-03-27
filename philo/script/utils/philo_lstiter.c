/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 philo_lstiter.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: emaillet <emaillet@student.42lehavre.fr	+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/02/27 07:40:35 by emaillet		   #+#	  #+#			  */
/*	 Updated: 2025/03/27 17:28:42 by emaillet		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../philo.h"

void	philo_lstiter_pthj(t_list *lst)
{
	t_philo	*philo;

	while (lst)
	{
		philo = (t_philo *)lst->content;
		pthread_join(philo->thread, NULL);
		if (PHILO_DEBUG)
			printf(RED"Philo thread	%ld	is join"RES, philo->id);
		lst = lst->next;
	}
}

void	philo_lstiter_r_fork(t_list	*lst_head, t_philo_data	*data)
{
	t_philo	*philo;
	t_philo	*philo_n;
	t_list	*lst;

	lst = lst_head;
	if (!lst)
		return ;
	while (lst)
	{
		philo = (t_philo *)lst->content;
		if (data->fork_c <= 1)
			philo->r_fork = NULL;
		else if (lst->next != NULL)
			philo_n = (t_philo *)lst->next->content;
		else
			philo_n = (t_philo *)lst_head->content;
		philo->r_fork = philo_n->l_fork;
		lst = lst->next;
	}
}

int	philo_lstiter_end(t_list *lst_head,	t_philo_data *data)
{
	t_philo	*philo;
	t_list	*lst;
	int		full_count;

	(void)data;
	full_count = 0;
	lst = lst_head;
	while (lst)
	{
		philo = lst->content;
		pthread_mutex_lock(&philo->state_mutex);
		if (philo->isdead == 1)
		{
			pthread_mutex_unlock(&philo->state_mutex);
			return (0);
		}
		if (!philo->isfull)
			full_count = 1;
		pthread_mutex_unlock(&philo->state_mutex);
		lst = lst->next;
	}
	return (full_count);
}

void	philo_launcher(t_list *lst_head, t_philo_data *data)
{
	t_philo		*philo;
	t_list		*lst;
	t_philargs	*arg;

	lst = lst_head;
	while (lst != NULL)
	{
		ft_lstadd_front(ft_alist(),
			ft_lstnew(arg = ft_calloc(1, sizeof(t_philargs))));
		arg->data = data;
		philo = lst->content;
		arg->philo = philo;
		gettimeofday(&arg->philo->cur_time, NULL);
		gettimeofday(&arg->philo->last_eat_time, NULL);
		gettimeofday(&arg->philo->start_time, NULL);
		gettimeofday(&arg->philo->last_update_time, NULL);
		pthread_create(&arg->philo->thread,
			NULL, (void *)philo_loop, (void *)arg);
		usleep(ONE_MS / 5);
		lst = lst->next;
	}
}
