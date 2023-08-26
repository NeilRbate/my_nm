/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:04:37 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:41:25 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*stock;

	i = 0;
	stock = (unsigned char *)b;
	while (i < len)
	{
		*stock++ = (unsigned char)c;
		i++;
	}
	return (b);
}
