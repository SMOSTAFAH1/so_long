/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:00 by rexposit          #+#    #+#             */
/*   Updated: 2025/03/05 10:00:00 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_base(unsigned long long n, char *base, int base_len, int *count)
{
	if (n >= (unsigned long long)base_len)
		print_base(n / base_len, base, base_len, count);
	write(1, &base[n % base_len], 1);
	(*count)++;
}

static void	handle_format(va_list args, const char format, int *count)
{
	if (format == 'c')
	{
		char c = va_arg(args, int);
		write(1, &c, 1);
		(*count)++;
	}
	else if (format == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (format == 'p')
	{
		void *ptr = va_arg(args, void *);
		ft_putstr("0x", count);
		print_base((unsigned long long)ptr, "0123456789abcdef", 16, count);
	}
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (format == 'u')
		print_base(va_arg(args, unsigned int), "0123456789", 10, count);
	else if (format == 'x')
		print_base(va_arg(args, unsigned int), "0123456789abcdef", 16, count);
	else if (format == 'X')
		print_base(va_arg(args, unsigned int), "0123456789ABCDEF", 16, count);
	else if (format == '%')
	{
		write(1, "%", 1);
		(*count)++;
	}
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			handle_format(args, format[i], &count);
		}
		else if (format[i] != '%')
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
} 