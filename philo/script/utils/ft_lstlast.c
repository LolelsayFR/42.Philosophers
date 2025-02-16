/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:28:56 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/19 02:36:35 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

//#include <stdio.h>
//
//void	ft_lstprint(t_list *liste)
//{
//	t_list	*tmp;
//	char	*s;
//
//	tmp = liste;
//	while (tmp != NULL)
//	{
//		s = tmp->content;
//		printf("%s -> ", s);
//		tmp = tmp->next;
//	}
//	printf("NULL\n");
//}
//
//int	main(int argc, char *argv[])
//{
//	t_list	*test;
//
//	if (argc == 3)
//	{
//		test = ft_lstnew(ft_strdup(argv[1]));
//		ft_lstadd_back(&test, ft_lstnew(ft_strdup(argv[2])));
//		ft_lstadd_front(&test, ft_lstnew(ft_strdup(argv[0])));
//		ft_lstprint(test);
//		test = ft_lstlast(test);
//		ft_lstprint(test);
//	}
//	return (0);
//}
