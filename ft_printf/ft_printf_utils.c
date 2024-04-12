/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:06:49 by jakim             #+#    #+#             */
/*   Updated: 2024/03/21 12:12:51 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchr(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	ft_putpoint(void *s)
{
	unsigned long long	n;
	char				str[30];
	int					i;
	int					r;

	i = 0;
	n = (unsigned long long)s;
	if (!n)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	while (n)
	{
		str[i++] = "0123456789abcdef"[n % 16];
		n = n / 16;
	}
	r = i;
	while (i > 0)
		write(1, &str[--i], 1);
	return (r + 2);
}
