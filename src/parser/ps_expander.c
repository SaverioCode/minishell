/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:53:39 by sav               #+#    #+#             */
/*   Updated: 2023/06/21 18:02:15 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dollar_sub(char *str, int i, t_info *info)
{
	char	*var;
	char	*value;
	char	*new;
	char	*old;
	int		from;

	from = i;
	i += 1;
	while (str[i])
	{
		if (!ft_isprint(str[i]) || str[i] == '$' || str[i] == '"')
		{
			break ;
		}
		i++;
	}
	var = ft_getstr_from_to(str, from + 1, i - 1);
	old = ft_getstr_from_to(str, 0, from - 1);
	value = ms_get_env_value(info, var);
	new = ft_strjoin(old, value, 1 , 1);
	new = ft_strjoin(new, &str[i], 1, 0);
	free(str);
	free(var);
	return (new);
}

static char	*expansion(char *str, t_info *info)
{
	int		flag[2];
	int		i;

	flag[0] = 0;
	flag[1] = 0;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if ((!flag[0] || flag[1] == '"') && str[i] == '$')
		{
			str = dollar_sub(str, i, info);
		}
		i++;
	}
	str = ps_quotes_cleaner(str);
	return (str);
}

void	ps_expander(t_node *node, t_info *info)
{
	t_opr	*opr;
	size_t	i;

	if (node->cmd != NULL)
	{
		node->cmd->cmd = expansion(node->cmd->cmd, info);
		i = 0;
		if (node->cmd->args)
		{
			while (node->cmd->args[i])
			{
				node->cmd->args[i] = expansion(node->cmd->args[i], info);
				i++;
			}
		}
	}
	if (node->opr != NULL)
	{
		opr = node->opr;
		while (opr->next)
		{
			opr->path = expansion(opr->path, info);
			opr = opr->next;
		}
		opr->path = expansion(opr->path, info);
	}
}
