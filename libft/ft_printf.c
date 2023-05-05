/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:42:06 by delvira-          #+#    #+#             */
/*   Updated: 2022/12/16 22:52:53 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	func(va_list args, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += printchar(va_arg(args, int));
	if (c == 's')
		len += print_str(va_arg(args, char *));
	if (c == 'x')
		len += ft_print_hexlow(va_arg(args, unsigned int));
	if (c == 'X')
		len += ft_print_hexhigh(va_arg(args, unsigned int));
	if (c == '%')
		len += print_percent();
	if (c == 'd' || c == 'i')
		len += print_num(va_arg(args, int));
	if (c == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	if (c == 'p')
		len += ft_ptr_void (va_arg(args, unsigned long long));
	return (len);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '%')
			len += printchar(str[i]);
		else
		{
			len += func(args, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
