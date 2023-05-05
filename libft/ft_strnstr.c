/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:11:33 by delvira-          #+#    #+#             */
/*   Updated: 2022/10/10 18:02:05 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (needle[0] == '\0')
	{
		return ((char *) haystack);
	}
	while ((haystack[i] != '\0') && (i < len))
	{
		x = 0;
		while (haystack[i + x] != '\0' && haystack[i + x] == needle[x]
			&& ((i + x) < len))
		{
			if (needle[x + 1] == '\0')
			{
				return ((char *) &haystack[i]);
			}
			x++;
		}
		i++;
	}
	return (NULL);
}
