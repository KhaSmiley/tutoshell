/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 03:40:10 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/28 22:08:22 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_token *ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_stock(t_token **lst, t_token *new_link)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new_link;
	else
		(ft_lstlast(*lst))->next = new_link;
}

t_token	*ft_lstnew(char *content, int type)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->str = content;
    new->type = type;
	new->next = NULL;
	return (new);
}
void print_list(t_token *lst)
{
    if (!lst)
    {
		// ft_printf("EMPTY LIST\n");
		return ;
	
	}
    while(lst)
    {
        // ft_printf("WORD : %s TYPE : %d\n", lst->str, lst->type);
        lst = lst->next;
    }
    return ;
}