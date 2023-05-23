/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:21:51 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/22 16:16:18 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strjoin is not freeing str1 because it's used //
// only for create the info->prompt and as str1 //
// it takes getenv("USER"); that returns a static char * //

char    *ft_strjoin(char *str1, char *str2)
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
    j = 0;
    while (str2[j])
    {
        str[i + j] = str2[j];
        j++;
    }
    if (str2)
    {
        free(str2);
    }
    return (str);
}

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
    while (str2[j])
    {
        str[i + j] = str2[j];
        j++;
    }
    free(str1);
    free(str2);
    return (str);
}
