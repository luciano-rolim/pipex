/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:32:15 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/04/26 10:24:01 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

int		ft_printf(const char *s, ...);
void	print_putstr(char *s, int *len);
void	print_putchar(char c, int *len);
void	print_hex_pointer(void *pointer, int *len);
void	print_hexadecimal(size_t n, int *len, char c);
void	print_unsigned_putnbr(unsigned int n, int *len);
void	print_putnbr(int n, int *len);

#endif