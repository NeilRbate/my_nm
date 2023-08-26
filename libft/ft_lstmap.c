/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:16:57 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:35:32 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_1;
	t_list	*list_2;

	list_2 = 0;
	if (lst != 0 && f != 0 && del != 0)
	{
		while (lst)
		{
			list_1 = ft_lstnew((*f)(lst->content));
			if (list_1 == 0)
			{
				ft_lstclear(&list_2, (*del));
				return (0);
			}
			ft_lstadd_back(&list_2, list_1);
			lst = lst->next;
		}
	}
	else
		return (0);
	return (list_2);
}
