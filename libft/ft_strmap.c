/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 12:24:48 by mcarney           #+#    #+#             */
/*   Updated: 2018/07/09 12:24:48 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*map;
	size_t	i;

	if (!s || (!(map = ft_strnew(ft_strlen(s)))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		map[i] = f(s[i]);
		i++;
	}
	return (map);
}
