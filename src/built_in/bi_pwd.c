/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:39:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 18:03:25 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bi_get_cwd(void)
{
	char	*cwd;
	char	*buff;
	int		size;

	cwd = NULL;
	buff = NULL;
	size = 1;
	while (cwd == NULL)
	{
		free(cwd);
		free(buff);
		buff = ft_calloc(1, size);
		cwd = getcwd(buff, size);
		size++;
	}
	free(buff);
	return (cwd);
}

int	bi_pwd(char **args)
{
	char	*cwd;

	if (args != NULL)
	{
		write(2, "Error: to many arguments.\n", 26);
		return (1);
	}
	cwd = get_cwd();
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}
