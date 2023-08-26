/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:46:25 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:33:41 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	m;
	long	len;
	char	*ret;
	int		sign;

	m = (long)n;
	sign = 0;
	len = nb_len(m);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (0);
	ret[len] = '\0';
	if (m < 0)
	{
		sign = 1;
		m *= -1;
	}
	while (len-- > 0)
	{
		ret[len] = ((m % 10) + '0');
		m = m / 10;
	}
	if (sign)
		ret[0] = '-';
	return (ret);
}
