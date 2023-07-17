/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:53:39 by sav               #+#    #+#             */
/*   Updated: 2023/07/17 11:44:07 by fgarzi-c         ###   ########.fr       */
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
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			break ;
	}
	var = ft_getstr_from_to(str, from + 1, i - 1);
	value = ms_get_env_value(info, var);
	if (str[i] == '?')
	{
		value = ft_itoa(info->exit_status);
		i++;
	}
	old = ft_getstr_from_to(str, 0, from - 1);
	new = ft_strjoin(old, value, 1, 1);
	new = ft_strjoin(new, &str[i], 1, 0);
	free(str);
	free(var);
	return (new);
}

char	*ps_expand(char *str, t_info *info)
{
	int		flag[2];
	int		i;

	if (str == NULL)
	{
		return (NULL);
	}
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
	return (str);
}

static void	expand_opr_node(t_opr *node, t_info *info)
{
	t_opr	*opr;
	char	**arr;

	opr = node;
	while (opr)
	{
		arr = ps_quotes_cleaner(ps_wildcard(ps_expand(opr->path, info)));
		if (arr != NULL)
		{
			opr->path = ft_strcpy(arr[0]);
			ft_free_arr(arr);
			arr = NULL;
		}
		opr = opr->next;
	}
}

static void	expand_cmd_node(t_cmd *node, t_info *info)
{
	__uint32_t	i;
	char		**arr;

	arr = ps_quotes_cleaner(ps_wildcard(ps_expand(node->cmd, info)));
	if (arr != NULL)
	{
		node->cmd = ft_strcpy(arr[0]);
		ft_free_arr(arr);
		arr = NULL;
	}
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			node->args[i] = ps_expand(node->args[i], info);
			arr = ft_append_arr(arr, ps_wildcard(node->args[i]));
			arr = ps_quotes_cleaner(arr);
			i++;
		}
		free(node->args);
		node->args = arr;
	}
}

void	ps_expander(t_node *node, t_info *info)
{
	if (node->cmd != NULL)
	{
		expand_cmd_node(node->cmd, info);
	}
	if (node->opr != NULL)
	{
		expand_opr_node(node->opr, info);
	}
}
