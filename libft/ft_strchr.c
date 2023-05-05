/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:10:48 by delvira-          #+#    #+#             */
/*   Updated: 2022/10/10 18:00:46 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	caracter;
	char	*str;
	int		i;

caracter = c;
str = (char *)s;
i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == caracter)
		{
			return (&str[i]);
		}
	i++;
	}
	if (str[i] == '\0' && caracter == '\0')
	{
		return (&str[i]);
	}
	return (NULL);
}
