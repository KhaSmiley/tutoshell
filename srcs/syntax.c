/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 22:49:38 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/28 18:50:16 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int ft_syntax_pipe(t_token *tok)
{
    t_token *tmp;
    
    if (!tok)
        return (12);
    tmp = tok;
    if (tmp->type == PIPE)
        return (35);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp))
            return (59);
    }
    return (0);
}

int ft_syntax_redir(t_token *tok)
{
    t_token *tmp;

    if(!tok)
        return (112);
    tmp = tok;
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
        return (1543);
    else if (tmp->type == PIPE)
        return (13252);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        if (ft_syntax_word(tmp))
            return (154354);
    }
    return (0);
}

int ft_syntax_word(t_token *tok)
{
    t_token *tmp;
    int error;

    tmp = tok;
    while (tmp && tmp->type == WORD)
        tmp = tmp->next;
    if (!tmp)
        return (0);
    if (tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS)
    {
        tmp = tmp->next;
        error = ft_syntax_redir(tmp);
        if (error)
            return (error);
    }
    else if (tmp->type == PIPE)
    {
        tmp = tmp->next;
        error = ft_syntax_pipe(tmp);
        if (error)
            return (error);
    }
    return (0);
}

/*
    if tab[0] == PIPE

    if tab[i] == PIPE && tab[i + 1] == PIPE

    if tab[dernier] == PIPE ou CHEVRON
    
    if tab[i] == CHEVRON && tab[i + 1] == CHEVRON ou PIPE


    OK
    tab[i] == PIPE && tab[i + 1] == CHEVRON
*/

int ft_syntax(t_token *tok)
{
    t_token *tmp;

    int error;
    tmp = tok;
    if ((tmp->type == GREATER || tmp->type == LESS || tmp->type == DGREATER || tmp->type == DLESS))
    {
        if (tmp->next == NULL)
            return (ft_printf("syntax error near unexpected token `newline'\n"), -1);
        tmp = tmp->next;
        error = ft_syntax_redir(tmp);
        if (error)
            return (ft_printf("Syntax Error [%i]\n", error), -1);
        return (0);            
    }
    else if (tmp->type == PIPE)
        return (ft_printf("syntax error near unexpected token '|'\n"), -1);
    else if (tmp->type == WORD)
    {
        tmp = tmp->next;
        error = ft_syntax_word(tmp);
        if (error)
            return (ft_printf("Syntax Error [%i]\n", error), -1);
    }
    return (0);
}
