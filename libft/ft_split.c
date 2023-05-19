/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:11:48 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/19 19:30:09 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findchar(char c, char s)
{
	if (s == c)
		return (1);
	return (0);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	last;
	int	wc;

	wc = 0;
	last = 1;
	i = 0;
	while (s[i])
	{
		if (ft_findchar(c, s[i]) == 0 && last == 1)
		{
			wc++;
		}
		last = ft_findchar(c, s[i]);
		i++;
	}
	return (wc);
}

static void	ft_free(char **strs, int x)
{
	while (x-- > 0)
		free(strs[x]);
	free(strs);
}

static int	ft_wordlen(const char *s, char c, int index)
{
	int	i;

	i = index + 1;
	while (ft_findchar(c, s[i]) == 0 && s[i] != '\0')
	{
		i++;
	}
	return (i - index);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		x;

	x = 0;
	i = 0;
	strs = (char **) malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (x < ft_wordcount(s, c))
	{
		while (s[i] == c)
			i++;
		strs[x] = ft_substr(s, i, ft_wordlen(s, c, i));
		if (!strs[x])
		{
			ft_free(strs, x);
			return (NULL);
		}
		i += ft_wordlen(s, c, i);
		x++;
	}
	strs[x] = 0;
	return (strs);
}
