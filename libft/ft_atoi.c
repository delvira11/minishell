/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:06:32 by delvira-          #+#    #+#             */
/*   Updated: 2022/10/10 17:48:56 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sig;
	int	sol;

	i = 0;
	sig = 1;
	sol = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
		{
			sig *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sol *= 10;
		sol += str[i] - '0';
		i++;
	}
	return (sol * sig);
}
