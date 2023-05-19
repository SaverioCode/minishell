/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:21:51 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 21:41:17 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin_sp(char *str1, char *str2)
{
    char      *str;
    int       len;
    size_t     i;
    size_t     j;

    len = ft_strlen(str1) + ft_strlen(str2);
    str = ft_calloc(len + 2, 1);
    i = 0;
    while (str1[i])
    {
        str[i] = str1[i];
        i++;
    }
    str[i] = 32;
    i++;
    j = 0;
    while (str2[0])
    {
        str[i + j] = str2[j];
        j++;
    }
    free(str1);
    free(str2);
    return (str);
}
