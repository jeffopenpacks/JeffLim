/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:59:27 by joolim            #+#    #+#             */
/*   Updated: 2023/09/14 12:01:12 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*holdlist;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		holdlist = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = holdlist;
	}
	*lst = NULL;
}
