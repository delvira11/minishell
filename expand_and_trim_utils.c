/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_trim_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:03:35 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/09 16:31:53 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_char_in_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*my_trim(char *s1, char *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	free(s1);
	return (str);
}

void	free_string_array(char	**strarray)
{
	int	x;

	x = 0;
	while (strarray[x])
	{
		free(strarray[x]);
		x++;
	}
	free(strarray);
}

t_counters	init_counters(void)
{
	t_counters	c;

	c.i = 0;
	c.x = 0;
	c.j = 0;
	c.n = 0;
	return (c);
}

char	*free_and_return(char *str, char *replace, char *str_return)
{
	free(str);
	if (replace[0] != '\0')
		free(replace);
	return (str_return);
}
