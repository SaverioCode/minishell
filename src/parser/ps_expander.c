/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:53:39 by sav               #+#    #+#             */
/*   Updated: 2023/06/10 01:45:24 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *strjoin_in_the_middle(char *str1, int to, char *str2, char *str3)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = to + ft_strlen(str2) + ft_strlen(str3);
	new_str = ft_calloc(1, len + 1);
	i = -1;
	while (++i <= to)
		new_str[i] = str1[i];
	j = 0;
	while (str2 && str2[j])
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	j = 0;
	while (str3[j])
	{
		new_str[i + j] = str3[j];
		j++;
	}
	free(str1);
	free(str2);
	return (new_str);
}

static char	*get_var_value(char *var, char **env)
{
	char	*value;
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	value = NULL;
	printf("var: |%s|\n", var);////////
	while (env[i])
	{
		if (ft_strlen(env[i]) >= len)
		{
			if (ft_strncmp(var, env[i], len - 2) == 1)
			{
				printf("value before: |%s|\n", env[i] - 1);////////
				value = ft_strjoin(&env[i][len], NULL, 0, 0);
			}
		}
		i++;
	}
	printf("value: |%s|\n", value);////////
	return (value);
}

static char	*dollar_sub(char *str, int i, char **env)
{
	char	*var;
	char	*value;
	int		from;

	from = i;
	write(1, "DOLSUB0\n", 8);/////////////////
	while (str[i])
	{
		if (!ft_isprint(str[i]) || str[i] == '$' || str[i] == '"')
		{
			break ;
		}
		i++;
	}
	printf("|||%s|||\n", str);////////////////
	var = ft_getstr_from_to(str, from + 1, i - 1);
	printf("|||%s|||\n", var);////////////////
	write(1, "DOLSUB1\n", 8);/////////////////
	value = get_var_value(var, env);
	write(1, "DOLSUB2\n", 8);/////////////////
	str = strjoin_in_the_middle(str, from - 1, var, &str[i]);
	write(1, "DOLSUB3\n", 8);/////////////////
	printf("str: |%s|\n", str);////////
	free(var);
	return (str);
}

static char	*expansion(char *str, char **env)
{
	char	*fallback;
	int		flag[2];
	int		i;

	//// I don't really need this check I have to be sure that without env ////
	//// I return blank when expanding ////
	if (env == NULL)
	{
		fallback = ft_calloc(1, 1);
		return (fallback);
	}
	flag[0] = 0;
	flag[1] = 0;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if ((!flag[0] || flag[1] == '"') && str[i] == '$')
		{
			str = dollar_sub(str, i, env);
		}
		i++;
	}
	str = ps_quotes_cleaner(str);
	return (str);
}

void	ps_expander(t_node *node, char **env)
{
	t_opr	*opr;
	size_t	i;

	if (node->cmd != NULL)
	{
		node->cmd->cmd = expansion(node->cmd->cmd, env);
		i = 0;
		if (node->cmd->args)
		{
			while (node->cmd->args[i])
			{
				node->cmd->args[i] = expansion(node->cmd->args[i], env);
				i++;
			}
		}
	}
	if (node->opr != NULL)
	{
		opr = node->opr;
		while (opr->next)
		{
			opr->path = expansion(opr->path, env);
			opr = opr->next;
		}
		opr->path = expansion(opr->path, env);
	}
}
