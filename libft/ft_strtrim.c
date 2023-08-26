/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:48:45 by jbarbate          #+#    #+#             */
/*   Updated: 2022/11/09 15:43:40 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char				*ret;
	unsigned int		start;
	unsigned int		end;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	if (start != end)
		while (ft_strchr(set, s1[end]) && end > start)
			end--;
	ret = ft_substr(s1, start, (end - start + 1));
	return (ret);
}
