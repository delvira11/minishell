/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:11:51 by delvira-          #+#    #+#             */
/*   Updated: 2022/10/10 17:58:58 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	simbolo;
	unsigned char	*str;

simbolo = c;
str = b;
i = 0;
	while (i < len)
	{
		str[i] = simbolo;
		i++;
	}
	return (b);
}
