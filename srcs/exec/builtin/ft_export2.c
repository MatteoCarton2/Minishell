/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:54:38 by mcarton           #+#    #+#             */
/*   Updated: 2025/06/20 17:26:37 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*get_key(char *str)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (ft_strdup(str));
	key = ft_substr(str, 0, equal - str);
	return (key);
}

int	check_line(char ***env, char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = get_key(str);
	if (key)
	{
		while ((*env)[i])
		{
			if (ft_strncmp((*env)[i], key, ft_strlen(key)) == 0
				&& ((*env)[i][ft_strlen(key)] == '='
					|| (*env)[i][ft_strlen(key)] == '\0'))
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(str);
				free(key);
				return (0);
			}
			i++;
		}
		free(key);
		return (1);
	}
	else
		return (0);
}

static int	equal_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	show_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

char	*get_quoted(char *env)
{
	char	*quoted;
	int		i;
	int		pos;
	int		j;

	i = -1;
	j = 0;
	if (!env)
		return (NULL);
	pos = equal_pos(env);
	quoted = malloc(sizeof(char) * (ft_strlen(env) + 3));
	if (!quoted)
		return (NULL);
	while (env[++i])
	{
		quoted[j++] = env[i];
		if (i == pos && pos != -1)
			quoted[j++] = '"';
	}
	if (pos != -1)
		quoted[j++] = '"';
	quoted[j] = '\0';
	return (quoted);
}
