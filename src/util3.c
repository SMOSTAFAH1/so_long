/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:33:31 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:33:31 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

char	*ft_parse_line(char **keep, char **tmp)
{
	char	*line;

	if (!*keep || **keep == '\0')
		return (NULL);
	*tmp = ft_strdup(*keep);
	ft_free_strs(keep, 0, 0);
	line = get_before_newline(*tmp);
	*keep = get_after_newline(*tmp);
	ft_free_strs(tmp, 0, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*keep[FOPEN_MAX];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!keep[fd])
		keep[fd] = ft_strdup("");
	if (!keep[fd])
		return (NULL);
	tmp = NULL;
	ft_read_line(fd, &keep[fd], &tmp);
	if (!keep[fd])
		return (NULL);
	line = ft_parse_line(&keep[fd], &tmp);
	if (!line)
		ft_free_strs(&keep[fd], &line, &tmp);
	return (line);
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
