/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:48:35 by joolim            #+#    #+#             */
/*   Updated: 2023/10/29 14:39:06 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	printit2(char c, va_list args)
{
	if (c == 'c')
		return (specc(va_arg(args, int)));
	if (c == 's')
		return (specs(va_arg(args, const char *)));
	if (c == 'p')
		return (specp(va_arg(args, void *)));
	if (c == '%')
		return (specmod());
	if (c == 'd' || c == 'i')
		return (specd(va_arg(args, int)));
	if (c == 'x')
		return (specx(va_arg(args, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (specx(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (c == 'u')
		return (specu(va_arg(args, unsigned int)));
	return (0);
}

static int	checkchr(char c, const char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	printit(const char *format, va_list args)
{
	int	len;
	int	tlen;

	len = 0;
	while (*format)
	{
		if (*format == '%' && checkchr(*(format + 1), "cspdiuxX%"))
		{
			tlen = printit2(*(format + 1), args);
			if (tlen < 0)
				return (tlen);
			else
			{
				len += tlen;
				format += 2;
			}
		}
		else if (*format == '%')
			format++;
		else
			len += specc(*format++);
	}
	return (len);
}
