/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:18:42 by jakim             #+#    #+#             */
/*   Updated: 2024/03/21 12:04:18 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	formatting(char c, va_list args)
{
	if (!c)
		return (write(1, "%", 1));
	if (c == 'c')
		return (ft_putchr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putpoint(va_arg(args, void *)));
	else if (c == 'd')
		return (ft_putnbr(va_arg(args, int), 1));
	else if (c == 'i')
		return (ft_putnbr(va_arg(args, int), 1));
	else if (c == 'u')
		return (ft_putunbr_fd(va_arg(args, unsigned int), 1));
	else if (c == 'x')
		return (ft_putsix(va_arg(args, unsigned int), 1));
	else if (c == 'X')
		return (ft_putsix(va_arg(args, unsigned int), 0));
	else if (c == '%')
		return (write(1, "%", 1));
	write(1, "%", 1);
	write(1, &c, 1);
	return (2);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;

	i = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			i += formatting(*format, args);
			if (!*format)
				break ;
		}
		else
			i += write(1, format, 1);
		format++;
	}
	return (i);
}
