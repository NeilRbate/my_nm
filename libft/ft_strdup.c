/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:31:38 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/13 09:40:34 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
	return (ret);
}
