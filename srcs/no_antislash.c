/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_antislash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:17:48 by zdnaya            #+#    #+#             */
/*   Updated: 2021/03/01 13:00:05 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_antislach(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            i = spl_quote(s, i + 1);
        else if (s[i] == '\\')
            return (1);
        i++;
    }
    return (0);
}

char *slach(char *s)
{
    if (check_antislach(s) == 1)
        return (no_antislach(s));
    else
        return (s);
}

int count_slash(char *s, int i)
{
    int j;

    j = 0;
    while (s[i] == '\\' && s[i])
    {
        j++;
        i++;
    }
    return (j);
}

int alloc_slach(char *s, int i)
{
    int j;

    j = 0;
    if (i == 0)
    {
        if (s[i] == '\'')
            i = spl_quote(s, i + 1);
        if (s[i] == '\"')
        {
            i = dbl_quote(s, i + 1);
            j = dbl_quote(s, i + 1);
        }
    }
    while (s[i])
    {
        if (s[i] == '\'' && i > 0 && s[i - 1] != '\\')
            i = spl_quote(s, i + 1);
        if (s[i] == '\"' && i > 0 && s[i - 1] != '\\')
        {
            i = dbl_quote(s, i + 1);
            j = dbl_quote(s, i + 1);
        }
        else
        {
            while (s[i] != '\\' && s[i])
            {
                j++;
                i++;
            }
            if (j != 0)
                return (j);
        }
        i++;
    }
    return (j);
}

char *no_antislach(char *string)
{
    char *str;
    char *tmp;
    t_use use;

    ft_bzero(&use, sizeof(t_use));

    str = ft_strdup(string);
    if (!(tmp = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (NULL);
    use.i = 0;
    while (str[use.i] != '\0')
    {
        use.u = 0;
        use.w = 0;
        use.j = 0;
        use.k = 0;
        if (str[use.i] == '\"')
            tmp = _no_slash_norm(str, &use, tmp);
        if (str[use.i] == '\'')
        {
            use.j = 0;
            use.u = spl_quote(str, use.i + 1) + 1;
            if (!(use.str1 = malloc(sizeof(char) * (use.u + 1))))
                return (NULL);
            while (use.i < use.u && str[use.i])
                use.str1[use.j++] = str[use.i++];
            use.str1[use.j] = '\0';
        }
        if (str[use.i] == '\\')
        {
            use.k = 0;
            use.w = count_slash(str, use.i);
            if (use.w % 2 != 0)
            {
                use.i++;
                use.u = (use.w - 1) / 2;
                if (!(use.s1 = malloc(sizeof(char) * (use.u + 1))))
                    return (NULL);
                use.i = use.i + use.u;
                if (use.u != 0)
                {
                    while (str[use.i] == '\\' && str[use.i])
                        use.s1[use.k++] = str[use.i++];
                    use.s1[use.k] = '\0';
                }
            }
            else if (use.w % 2 == 0)
            {
                use.u = (use.w) / 2;
                if (!(use.s1 = malloc(sizeof(char) * (use.u + 1))))
                    return (NULL);
                use.i = use.i + use.u;
                while (str[use.i] == '\\' && str[use.i])
                    use.s1[use.k++] = str[use.i++];
                use.s1[use.k] = '\0';
            }
            tmp = join_dolar(tmp, use.s1);
        }
        else
        {
            use.j = 0;
            if (!(use.str1 = malloc(sizeof(char) * (alloc_slach(str,use.i) + 1))))
                return (NULL);
            while (str[use.i] != '\\' && str[use.i])
                use.str1[use.j++] = str[use.i++];
            use.str1[use.j] = '\0';
            tmp = join_dolar(tmp, use.str1);
        }
    }
    ft_stringdel(&str);
    return (tmp);
}
