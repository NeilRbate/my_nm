/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:30:36 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:34:37 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;

	if (lst != 0 && del != 0)
	{
		while (*lst)
		{
			list = (*lst)->next;
			ft_lstdelone((*lst), del);
			(*lst) = list;
		}
	}
}
