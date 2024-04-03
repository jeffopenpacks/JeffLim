/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:36:13 by joolim            #+#    #+#             */
/*   Updated: 2023/10/29 14:40:38 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	specx(unsigned int n, const char *base)
{
	int	len;

	len = 0;
	if (n > 15)
	{
		len += specx(n / 16, base);
		(void)specc(base[n % 16]);
		len++;
	}
	else
		len += specc(base[n]);
	return (len);
}
