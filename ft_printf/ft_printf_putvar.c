/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putvar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:54:05 by jakim             #+#    #+#             */
/*   Updated: 2024/03/21 12:15:56 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	sign(int n, int *base, char *str, int *flag)
{
	str[1] = 0;
	*base = 1000000000;
	*flag = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		return (-1);
	}
	else if (n == 0)
	{
		write(1, "0", 1);
		return (0);
	}
	else
		return (1);
}

int	unsign(unsigned int n, unsigned int *base, char *str, int *flag)
{
	str[1] = 0;
	*base = 1000000000;
	*flag = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (0);
	}
	else
		return (1);
}

int	ft_putnbr(int n, int fd)
{
	int		base;
	int		flag;
	char	str[2];
	int		s;

	s = sign(n, &base, str, &flag);
	if (s == 0)
		return (1);
	while (base)
	{
		if (!(n / base) && flag > 0)
		{
			write(fd, "0", 1);
			flag++;
		}
		if (n / base)
		{
			flag += 1;
			str[0] = ((n / base) * s) + '0';
			write (fd, str, 1);
		}
		n = n % base;
		base = base / 10;
	}
	return (flag + (s == -1));
}

int	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned int	base;
	int				flag;
	char			str[2];

	if (!unsign(n, &base, str, &flag))
		return (1);
	while (base)
	{
		if (!(n / base) && flag > 0)
		{
			write(fd, "0", 1);
			flag++;
		}
		if (n / base)
		{
			flag += 1;
			str[0] = (n / base) + '0';
			write (fd, str, 1);
		}
		n = n % base;
		base = base / 10;
	}
	return (flag);
}

int	ft_putsix(unsigned int n, int t)
{
	char			str[30];
	int				i;
	int				r;

	i = 0;
	if (!n)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n)
	{
		if (t)
			str[i++] = "0123456789abcdef"[n % 16];
		else
			str[i++] = "0123456789ABCDEF"[n % 16];
		n = n / 16;
	}
	r = i;
	while (i > 0)
		write(1, &str[--i], 1);
	return (r);
}
