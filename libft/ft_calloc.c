/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:57:18 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:32:23 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (size && count && ((unsigned long)count * (unsigned long)size) == 0)
		return (0);
	if (count != 0 && size >= SIZE_MAX / count)
		return (0);
	ret = malloc(count * size);
	if (ret == 0)
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
