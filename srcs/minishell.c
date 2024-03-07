/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:36 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/28 22:24:21 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int     ft_tokenizer(char *token)
{
    if (ft_strcmp(token, "<") == 0)
        return (LESS);
    else if (ft_strcmp(token, ">") == 0)
        return (GREATER);
    else if (ft_strcmp(token, "<<") == 0)
        return (DLESS);
    else if (ft_strcmp(token, ">>") == 0)
        return (DGREATER);
    else if (ft_strcmp(token, "|") == 0)
        return (PIPE);
    else if (ft_strcmp(token, " ") == 0)
        return (WSPACE);
    else
        return (WORD);
} 

int word_size(char *str, int i)
{
    int j;

    j = 0;
    while(str[i] != ' ' && str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '\0')
    {
        j++;
        i++;
    }
    return (j);
}   

int    alloc_token(t_token **tok, char *longchev, char *str, int i)
{
    if (str[i + 1] == longchev[0])
    {
        ft_stock(tok, ft_lstnew(longchev, ft_tokenizer(longchev)));
        return (1);
    }
    ft_stock(tok, ft_lstnew(&longchev[1], ft_tokenizer(&longchev[1])));  
    return (0);
}


int    find_token(char *str)
{
    int i;
    int j;
    char *word;
    t_token *tok;
    
    tok = NULL;
    i = 0;
    if (!str[0])
        return (1);
    while(str[i])
    {
        if (str[i] == '<')
            i += alloc_token(&tok, "<<", str, i);
        else if (str[i] == '>')
            i += alloc_token(&tok, ">>", str, i);
        else if (str[i] == '|')
            ft_stock(&tok, ft_lstnew("|", ft_tokenizer("|")));
        else if (str[i] == ' ')
            ft_tokenizer(" ");
        else
        {
            j = 0;
            word = malloc(word_size(str, i) + 1);
            while (ft_strchr(" \t><|\0", str[i]) == 0) // ft_
                word[j++] = str[i++];
            word[j] = '\0';
            ft_stock(&tok, ft_lstnew(word, ft_tokenizer(word)));
            i--;
        }
        i++;
    }
    // print_list(tok);
    if (ft_syntax(tok))
        return (1);
    return(0);
}   

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     (void)envp;
//     while (1)
//     {
//         char *input = readline("> ");
//         if (!input)
//             break;
//         if (!*input)
//             continue;
//         add_history(input);
//         find_token(input);
//     }
//     return (0);
// }