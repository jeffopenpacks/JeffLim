/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:48:55 by joolim            #+#    #+#             */
/*   Updated: 2023/09/13 12:41:53 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	size_t	total_size;
	void	*allocated_mem;

	total_size = num_elements * element_size;
	if (element_size != 0 && total_size / element_size != num_elements)
		return (NULL);
	allocated_mem = malloc(total_size);
	if (allocated_mem != NULL)
		ft_memset(allocated_mem, 0, total_size);
	return (allocated_mem);
}
