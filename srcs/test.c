/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:29:38 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/20 05:06:10 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
int ft_find_size(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(str[i])
    {
        if ((str[i] == '<' && str[i + 1] == '<' || str[i] == '>' && str[i + 1] == '>') && (str[i + 2] == ' ' && str[i - 1] == ' '))
        {
            printf("j'ajoute");
            j += 3;
        }   
        else if ((str[i] == '<' && str[i + 1] == '<' || str[i] == '>' && str[i + 1] == '>') && (str[i + 2] == ' ' && str[i - 1] != ' '))
        {
            printf("j'ajoute");
            j += 2;
        }    
        else if ((str[i] == '<' && str[i + 1] == '<' || str[i] == '>' && str[i + 1] == '>') && (str[i + 2] != ' ' && str[i - 1] == ' '))
        {
            printf("j'ajoute");
            j += 2;
        }    
        if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && (str[i + 1] == ' ' && str[i - 1] == ' '))
        {
            printf("j'ajoute");
            j += 2;
        }
        else if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && (str[i + 1] == ' ' && str[i - 1] != ' '))
            j += 1;
        else if ((str[i] == '<' || str[i] == '>' || str[i] == '|') && (str[i + 1] != ' ' && str[i - 1] == ' '))
            j += 1;
        j++;
        i++;
    }
    return (j);
}

char *ft_addspaces(char *str)
{
    int i;
    int size_before;
    int size_after;

    i = 0;
    size_before = ft_strlen(str);
    size_after = ft_find_size(str);
    printf("size after = %d\n", size_after);    
}

int main(int argc, char **argv)
{
    if (argc == 3)
        ft_addspaces(argv[1]);
    printf("%d\n", ft_strlen(argv[2]));
}