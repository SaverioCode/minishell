/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:53:39 by sav               #+#    #+#             */
/*   Updated: 2023/05/17 17:43:01 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *strjoin_in_the_middle(char *str1, int to, char *str2, char *str3)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = i + ft_strlen(str2) + ft_strlen(str3);
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
	while (str3 && str3[j])
	{
		new_str[i + j] = str3[j];
		j++;
	}
	free(str1);
	free(str2);
	return (new_str);
}

static char	*dollar_sub(char *str, int i)
{
	char	*var;
	char	*value;
	int		from;

	from = i;
	while (str[i])
	{
		if (!ft_isprint(str[i]) || str[i] == '$' || str[i] == '"')
			break ;
		i++;
	}
	var = ft_getstr_from_to(str, from + 1, i - 1);
	value = get_varvalue(var);
	if (!value)
	{
		free(var);
		return (str);
	}
	str = strjoin_in_the_middle(str, from - 1, var, &str[i]);
	free(var);
	return (str);
}

static char	*expansion(char *str, t_env *env)
{
	int		flag[2];
	int		i;

	flag[0] = 0;
	flag[0] = 0;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if ((!flag[0] || flag[1] == '"') && str[i] == '$')
		{
			str = dollar_sub(str, i);
		}
		i++;
	}
	return (str);
}

void	ps_expander(t_node *node, t_env *env)
{
	t_opr	*opr;
	size_t	i;

	node->cmd->cmd = expansion(node->cmd->cmd, env);
	i = 0;
	while (node->cmd->args[i])
	{
		node->cmd->args[i] = expansion(node->cmd->args[i], env);
		i++;
	}
	opr = node->opr;
	while (opr->next)
	{
		opr->arg = expansion(opr->arg, env);
		opr = opr->next;
	}
	opr->arg = expansion(opr->arg, env);
}
