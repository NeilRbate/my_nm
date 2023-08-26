/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:36:40 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:32:00 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(const char *str)
{
	if (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	stock;
	long	sign;

	i = 0;
	stock = 0;
	sign = 1;
	while (ft_isspace(&str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		stock *= 10;
		stock += (str[i] - 48);
		i++;
	}
	return ((stock * sign));
}
