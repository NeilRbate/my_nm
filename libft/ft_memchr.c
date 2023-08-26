/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:04:09 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:42:44 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*stock;

	i = 0;
	stock = (unsigned char *)s;
	while (i < n)
	{
		if (stock[i] == (unsigned char)c)
			return (stock + i);
		i++;
	}
	return (0);
}
