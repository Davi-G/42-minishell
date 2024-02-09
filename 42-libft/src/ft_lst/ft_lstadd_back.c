/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:17:28 by dagomez           #+#    #+#             */
/*   Updated: 2022/06/28 15:20:32 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	if (!new_lst)
		return ;
	if (!*lst)
	{
		*lst = new_lst;
		return ;
	}
	ft_lstlast(*lst)->next = new_lst;
}
