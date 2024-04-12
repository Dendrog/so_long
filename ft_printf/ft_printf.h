/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:19:39 by jakim             #+#    #+#             */
/*   Updated: 2024/03/21 12:17:05 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_putchr(char c);
int	ft_putstr(char *s);
int	ft_putpoint(void *s);
int	ft_putnbr(int n, int fd);
int	ft_putunbr_fd(unsigned int n, int fd);
int	ft_putsix(unsigned int n, int t);
int	ft_printf(const char *format, ...);

#endif
