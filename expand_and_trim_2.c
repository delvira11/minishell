/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_trim_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:19:25 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/16 17:47:32 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_var(char	*str)
{
	int		i;
	char	*env_var;
	int		j;
	int		countdoll;

	j = 0;
	i = 0;
	countdoll = 0;
	env_var = ft_calloc(1000, sizeof(char));
	while (str[i] != '$')
		i++;
	i++;
	while (str[i] != ' ' && str[i] != '\"' && str[i] != '\0' && str[i] != '\'')
	{
		env_var[j] = str[i];
		i++;
		j++;
	}
	return (env_var);
}

char	*find_replace(char	*str)
{
	char	*env_var;
	int		x;
	char	**aux_env;
	char	*return_replace;

	x = 0;
	env_var = find_env_var(str);
	while (environ[x])
	{
		aux_env = ft_split(environ[x], '=');
		if (!ft_strncmp(env_var, aux_env[0], ft_strlen(env_var)))
		{
			return_replace = aux_env[1];
			free(env_var);
			free(aux_env[0]);
			free(aux_env);
			return (return_replace);
		}
		free_string_array(aux_env);
		x++;
	}
	free(env_var);
	return ("");
}

char	*expand_dollar(char *str)
{
	t_norm_expand_var	norm;
	t_counters			c;

	c = init_counters();
	norm.str_return = ft_calloc(5000, sizeof(char));
	norm.replace = find_replace(str);
	while (str[c.i] != '\0')
	{
		if (str[c.i] == '$' && c.n == 0)
		{
			c.n = 1;
			c.j = c.i;
			while (str[c.j] != ' ' && str[c.j] != '\0'
				&& str[c.j] != '\'' && str[c.j] != '\"')
				c.j++;
			c.j -= c.i;
			c.i += c.j;
			c.j = 0;
			while (norm.replace[c.j] != '\0')
				norm.str_return[c.x++] = norm.replace[c.j++];
		}
		if (str[c.i] != '\0')
			norm.str_return[c.x++] = str[c.i++];
	}
	return (free_and_return(str, norm.replace, norm.str_return));
}

char	*multi_dollar(char	*str)
{
	return (expand_dollar(str));
}

char	*find_dollar(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i = 0;
			str = multi_dollar(str);
		}
		i++;
	}
	return (str);
}
