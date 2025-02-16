/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:28:20 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/19 02:35:41 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *lnew)
{
	t_list	*to_end;

	if (!lst || !lnew)
		return ;
	if (!*lst)
	{
		*lst = lnew;
		return ;
	}
	to_end = ft_lstlast(*lst);
	to_end->next = lnew;
}

//#include <stdio.h>
//
//void	ft_lstprint(t_list *liste)
//{
//	t_list	*tmp;
//
//	tmp = liste;
//	while (tmp != NULL)
//	{
//		printf("%s -> ", (char *)tmp->content);
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
//		ft_lstprint(test);
//	}
//	return (0);
//}
