/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:21:51 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 19:27:31 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char *str1, char *str2)
{
    char      *str;
    int       len;
    size_t     i;
    size_t     j;

    len = ft_strlen(str1) + ft_strlen(str2);
    str = ft_calloc(len + 1, 1);
    i = 0;
    while (str1[i])
    {
        str[i] = str1[i];
        i++;
    }
    j = 0;
    while (str2[0])
    {
        str[i + j] = str2[j];
        j++;
    }
    free(str1);
    free(str1);
    return (str);
}
