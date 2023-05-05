/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:05:08 by delvira-          #+#    #+#             */
/*   Updated: 2022/10/06 16:11:36 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			left;
	size_t			mem;
	unsigned int	i;

left = ft_strlen(s) - (size_t)start;
	if (left >= len)
	mem = len;
	if (left < len)
	mem = left;
	if (start > ft_strlen(s))
		mem = 0;
	str = (char *)ft_calloc((mem + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < mem)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}
