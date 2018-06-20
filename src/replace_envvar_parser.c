/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_envvar_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eliu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 07:53:09 by eliu              #+#    #+#             */
/*   Updated: 2018/06/20 07:55:51 by eliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*ft_get_env(char *name, char **env)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(name);
	while (env[++i])
	{
		if (!(ft_strncmp(env[i], name, len))
				&& env[i][len] == '=')
			return (ft_strchr(env[i], '=') + 1);
	}
	return (NULL);
}

void	add_env_entry(char *entry)
{
	size_t	envsize;
	char	**new_env;
	int		i;

	envsize = arr_length(g_environ);
	new_env = ft_memalloc((envsize + 2) * sizeof(*new_env));
	i = 0;
	while (g_environ[i])
	{
		new_env[i] = g_environ[i];
		++i;
	}
	new_env[i] = entry;
	free(g_environ);
	g_environ = new_env;
}

void	ft_set_env(char *name, char *val, char **env)
{
	int		i;
	size_t	len;
	char	*entry;

	entry = ft_strjoinv(2, "=", name, val);
	i = -1;
	len = ft_strlen(name);
	while (env[++i])
	{
		if (ft_strlen(env[i]) >= len)
			if (!(ft_strncmp(env[i], name, len)) && env[i][len] == '=')
			{
				env[i] = entry;
				return ;
			}
	}
	add_env_entry(entry);
}
