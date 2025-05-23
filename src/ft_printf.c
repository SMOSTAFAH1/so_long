/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-25 07:10:11 by shashemi          #+#    #+#             */
/*   Updated: 2024-09-25 07:10:11 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	print_base(unsigned long long n, char *base, int base_len, int *count)
{
	char	number;

	if (n >= (unsigned long long)base_len)
		print_base(n / base_len, base, base_len, count);
	number = base[n % base_len];
	*count += write(1, &number, 1);
}

static void	handle_char_pointer(char const *format, va_list argptr, int *count)
{
	int					aux;
	unsigned long long	addr;

	if (*format == 'c')
	{
		aux = va_arg(argptr, int);
		*count += write(1, &aux, 1);
	}
	else if (*format == 's')
		ft_putstr(va_arg(argptr, char *), count);
	else if (*format == 'p')
	{
		addr = va_arg(argptr, unsigned long long);
		if (addr == 0)
		{
			*count += write(1, "(nil)", 5);
			return ;
		}
		*count += write(1, "0x", 2);
		print_base(addr, "0123456789abcdef", 16, count);
	}
}

static void	parse_format(char const *format, va_list argptr, int *count)
{
	if (*format == 'c' || *format == 's' || *format == 'p')
		handle_char_pointer(format, argptr, count);
	else if (*format == 'd' || *format == 'i')
		ft_putnbr(va_arg(argptr, int), count);
	else if (*format == 'u')
		print_base(va_arg(argptr, unsigned int), "0123456789", 10, count);
	else if (*format == 'x')
		print_base(va_arg(argptr, unsigned int), "0123456789abcdef", 16, count);
	else if (*format == 'X')
		print_base(va_arg(argptr, unsigned int), "0123456789ABCDEF", 16, count);
	else if (*format == '%')
		*count += write(1, "%", 1);
}

int	ft_printf(char const *format, ...)
{
	int		count;
	va_list	argptr;

	count = 0;
	va_start(argptr, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			parse_format(++format, argptr, &count);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(argptr);
	return (count);
}

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		(*count)++;
	}
}

void	ft_putnbr(int nbr, int *count)
{
	char	c;
	long	n;

	n = nbr;
	if (n < 0)
	{
		write(1, "-", 1);
		(*count)++;
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10, count);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*count)++;
}
