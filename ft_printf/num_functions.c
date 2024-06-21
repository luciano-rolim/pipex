/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:18:51 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/04/26 10:24:34 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_putnbr(int n, int *len)
{
	if (n == -2147483648)
	{
		print_putstr("-2147483648", len);
		return ;
	}
	if (n < 0)
	{
		print_putchar('-', len);
		n *= -1;
	}
	if (n > 9)
	{
		print_putnbr(n / 10, len);
	}
	print_putchar(n % 10 + '0', len);
}

void	print_unsigned_putnbr(unsigned int n, int *len)
{
	if (n > 9)
	{
		print_unsigned_putnbr(n / 10, len);
	}
	print_putchar(n % 10 + '0', len);
}

void	print_hexadecimal(size_t n, int *len, char c)
{
	if (n >= 16)
		print_hexadecimal(n / 16, len, c);
	if (c == 'X')
		print_putchar("0123456789ABCDEF"[n % 16], len);
	if (c == 'x')
		print_putchar("0123456789abcdef"[n % 16], len);
}

void	print_hex_pointer(void *pointer, int *len)
{
	if (pointer == NULL)
	{
		write(1, "(nil)", 5);
		(*len) += 5;
		return ;
	}
	print_putchar('0', len);
	print_putchar('x', len);
	print_hexadecimal((size_t)pointer, len, 'x');
}
