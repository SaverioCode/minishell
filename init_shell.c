/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:50:59 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/02 18:03:41 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_shell(void)
{
	char	*dragon;

	dragon = calloc(1073, 1);
	dragon = "\033[H\033[38:5:9m\
				  /   \\\n\
 _                        )      ((   ))     (\n\
(@)                      /|\\      ))_((     /|\\                        _\n\
|-|                     / | \\    (/\\|/\\)   / | \\                      (@)\n\
| | -------------------/--|-voV---\\`|\'/--Vov-|--\\---------------------|-|\n\
|-|                         \'^`   (o o)  \'^`                          | |\n\
| |                               `\\Y/\'                               |-|\n\
|-|                                                                   | |\n\
| |                      Welcome to my minishell                      |-|\n\
|-|                                                                   | |\n\
| |                                                                   |-|\n\
|_|___________________________________________________________________| |\n\
(@)              l   /\\ /         ( (       \\ /\\   l                  |-|\n\
                 l /   V           \\ \\       V   \\ l                  (@)\n\
                 l/                _) )_          \\I\n\
                                   `\\ /\' 								\
								   ";
	printf("\033[2J");
	printf("%s\n", dragon);
	write(1, "\033[38:5:250m", 12);
}
