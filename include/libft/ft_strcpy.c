/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:28:47 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/30 17:43:41 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strcpy(char *str)
{
    char    *new;
    size_t  len;
    size_t  i;

    if (str == NULL)
    {
        return (NULL);
    }
    len = ft_strlen(str);
    new = ft_calloc(len + 1, 1);
    i = 0;
    while (str[i])
    {
        new[i] = str[i];
        i++;
    }
    return (new);
}