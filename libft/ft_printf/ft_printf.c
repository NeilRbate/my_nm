/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:57:21 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/22 09:21:44 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_write(char *s)
{
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (write(1, "(null)", 6), 6);
	while (s[i])
	{
		write(1, s + i, 1);
		i++;
	}
	return (i);
}

static unsigned int	nbase(unsigned long long nbr, char *base, int *ret)
{
	unsigned long long	nbr2;
	unsigned long long	i;

	if (nbr < 0)
		nbr2 = -nbr;
	else
		nbr2 = nbr;
	i = 0;
	while (base[i])
		i++;
	if (i > 1)
	{
		if (nbr2 < i)
			return (*ret += write(1, base + nbr2, 1));
		else
		{
			nbase((nbr2 / i), base, ret);
			nbase((nbr2 % i), base, ret);
		}
	}
	return (*ret);
}

static unsigned int	ft_print(const char format, va_list args)
{
	int		i;
	long	j;

	i = 0;
	if (format == 's')
		return (ft_write(va_arg(args, char *)));
	else if (format == 'u')
		return (nbase(va_arg(args, unsigned int), "0123456789", &i));
	else if (format == 'x')
		return (nbase(va_arg(args, unsigned int), "0123456789abcdef", &i));
	else if (format == 'X')
		return (nbase(va_arg(args, unsigned int), "0123456789ABCDEF", &i));
	else if (format == 'p')
		return ((write(1, "0x", 2) + nbase(va_arg(args, unsigned long long),
					"0123456789abcdef", &i)));
	else if (format == '%')
		return (write(1, "%", 1));
	else if (format == 'd' || format == 'i')
	{
		j = va_arg(args, int);
		if (j < 0)
			return ((write(1, "-", 1) + (nbase((j *= -1), "0123456789", &i))));
		return (nbase(j, "0123456789", &i));
	}
	return (write(1, &format, 1));
}

int	ft_printf(const char *format, ...)
{
	int		tab[3];
	va_list	args;

	tab[0] = -1;
	tab[1] = 0;
	va_start(args, format);
	while (format[++tab[0]])
	{
		if (format[tab[0]] == '%' && format[tab[0] + 1] == 'c')
		{
			tab[2] = va_arg(args, int);
			tab[1] += write(1, &tab[2], 1);
			tab[0]++;
		}
		else if (format[tab[0]] == '%')
			tab[1] += ft_print(format[++tab[0]], args);
		else
			tab[1] += write(1, format + tab[0], 1);
	}
	return (tab[1]);
}
