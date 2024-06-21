/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:27:48 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/05/31 20:50:41 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_putchar(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	print_putstr(char *s, int *len)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (s[i])
	{
		print_putchar(s[i], len);
		i++;
	}
}

static int	print_control(char c, va_list arguments, int *len)
{
	if (c == 'c')
		print_putchar(va_arg(arguments, int), len);
	else if (c == 's')
		print_putstr(va_arg(arguments, char *), len);
	else if (c == 'd' || c == 'i')
		print_putnbr(va_arg(arguments, int), len);
	else if (c == '%')
		print_putchar('%', len);
	else if (c == 'u')
		print_unsigned_putnbr(va_arg(arguments, unsigned int), len);
	else if (c == 'x')
		print_hexadecimal(va_arg(arguments, unsigned int), len, c);
	else if (c == 'X')
		print_hexadecimal(va_arg(arguments, unsigned int), len, c);
	else if (c == 'p')
		print_hex_pointer(va_arg(arguments, void *), len);
	else
		return (0);
	return (1);
}

int	ft_printf(const char *s, ...)
{
	va_list	arguments;
	int		i;
	int		len;

	if (!s)
		return (-1);
	i = 0;
	len = 0;
	va_start(arguments, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (!print_control(s[i], arguments, &len))
				i--;
		}
		else
			print_putchar(s[i], &len);
		i++;
	}
	va_end(arguments);
	return (len);
}
