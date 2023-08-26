/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:04:54 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:41:00 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	len_dst;
	unsigned int	i;

	if ((dst == 0 || src == 0) && size == 0)
		return (0);
	len_dst = 0;
	i = 0;
	while (dst[len_dst] && len_dst < size)
		len_dst ++;
	if (len_dst == size)
		return (size + ft_strlen(src));
	while (src[i] && len_dst < size - 1)
	{
		dst[len_dst] = src[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (len_dst + ft_strlen(src + i));
}
