/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:28:37 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/20 08:50:17 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!del || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
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
//		ft_lstclear(&test, free);
//		if (test)
//			ft_lstprint(test);
//		else
//			printf("GOOD clear ;P");
//	}
//	return (0);
//}
