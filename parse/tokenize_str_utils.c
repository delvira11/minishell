/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_str_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:41:22 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/09 15:50:11 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;
	size_t	i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)ft_calloc((s1len + s2len + 5), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1len + 1);
	i = 0;
	while (i < s2len)
	{
		str[s1len + i] = s2[i];
		i++;
	}
	free(s1);
	return (str);
}

char	*split_in_token(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(malloc_size(), sizeof(char));
	j = 0;
	while (cmd_line[i] == '<')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}

char	*split_out_token(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(malloc_size(), sizeof(char));
	j = 0;
	while (cmd_line[i] == '>')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}

char	*split_spaces_new(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(malloc_size(), sizeof(char));
	j = 0;
	while (cmd_line[i] != ' ' && cmd_line[i] != '"'
		&& cmd_line[i] != '\'' && cmd_line[i] != '\0'
		&& cmd_line[i] != '<' && cmd_line[i] != '>')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}
