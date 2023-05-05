/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:13:02 by delvira-          #+#    #+#             */
/*   Updated: 2022/12/02 14:59:46 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_unsigned_len(unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_uitoa(unsigned int n)
{
	char			*num;
	unsigned int	len;

	len = ft_unsigned_len(n);
	num = (char *)malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	len--;
	while (n > 0)
	{
		num[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (num);
}

int	ft_print_unsigned(unsigned int n)
{
	int		len;
	char	*str;
	int		i;

	if (n == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	len = ft_unsigned_len(n);
	str = ft_uitoa(n);
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	free (str);
	return (len);
}
