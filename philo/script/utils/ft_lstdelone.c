/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaillet <emaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:28:48 by emaillet          #+#    #+#             */
/*   Updated: 2025/01/20 12:50:10 by emaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del || !lst)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
		lst = NULL;
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
//	t_list	*temp;
//
//	if (argc == 3)
//	{
//		test = ft_lstnew(ft_strdup(argv[1]));
//		ft_lstadd_back(&test, ft_lstnew(ft_strdup(argv[2])));
//		ft_lstprint(test);
//		temp = test->next;
//		ft_lstdelone(test, free);
//		test = temp;
//		ft_lstprint(test);
//	}
//	return (0);
//}
