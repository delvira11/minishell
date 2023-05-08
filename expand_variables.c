/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:19:25 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/08 21:13:15 by delvira-         ###   ########.fr       */
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
	while (g_var.env[x])
	{
		aux_env = ft_split(g_var.env[x], '=');
		if (!ft_strncmp(env_var, aux_env[0], ft_strlen(env_var)))
		{
			return_replace = aux_env[1];
			return (return_replace);
		}
		x++;
	}
	return ("");
}



// ERROR CUANDO NO HAY ESPACIOS AL FINAL NO PONE LA ULTIMA COMILLA //

char	*expand_dollar(char *str)
{
	char	*replace;
	int		i;
	int		j;
	int		x;
	char	*str_return;
	int		n = 0;

	i = 0;
	x = 0;
	str_return = ft_calloc(5000, sizeof(char));
	replace = find_replace(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$' && n == 0)
		{
			n = 1;
			j = i;
			while (str[j] != ' ' && str[j] != '\0' && str[j] != '\'' && str[j] != '\"')
				j++;
			j -= i;
			i += j;
			j = 0;
			while (replace[j] != '\0')
				str_return[x++] = replace[j++];
			// while (str[i - 1] == '\'')
			// {
			// 	str_return[x++] = '\'';
			// 	i++;
			// }
			// printf("\n char: %c \n", str[i - 1]);
			// printf("\n str_ret: %s \n", str_return);
		}
		if (str[i] != '\0')
			str_return[x++] = str[i++];
	}
	return (str_return);
}

char	*multi_dollar(char	*str)
{
	return(expand_dollar(str));
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

char	**expand_variables(char **linesplitted)
{
	int	x;

	x = 0;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] != '\'')
		{
			linesplitted[x] = find_dollar(linesplitted[x]);
		}
		x++;
	}
	x = 0;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] == '\"')
			linesplitted[x] = ft_strtrim(linesplitted[x], "\"");
		else if (linesplitted[x][0] == '\'')
			linesplitted[x] = ft_strtrim(linesplitted[x], "\'");
		x++;
	}
	return (linesplitted);
}
