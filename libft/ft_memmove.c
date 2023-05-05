/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:48:15 by delvira-          #+#    #+#             */
/*   Updated: 2022/10/10 17:58:48 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;
	size_t			i;

i = 0;
source = (unsigned char *)src;
dest = (unsigned char *)dst;
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			dest[len] = source[len];
		}
	}
	if (dst < src)
	{
		while (i < len)
		{
		dest[i] = source[i];
		i++;
		}
	}
	return (dest);
}
