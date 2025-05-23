/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:00:00 by rexposit          #+#    #+#             */
/*   Updated: 2025/03/05 10:00:00 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	contains_newline(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_before_newline(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	res = ft_calloc(i + 1, sizeof(*res));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		res[i++] = '\n';
	return (res);
}

char	*get_after_newline(const char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (NULL);
	i++;
	j = i;
	while (s[j])
		j++;
	res = ft_calloc((j - i) + 1, sizeof(*res));
	if (!res)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		res[j] = s[i + j];
		j++;
	}
	return (res);
}

void	ft_read_line(int fd, char **keep, char **tmp)
{
	char	*buf;
	int		bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	bytes = 1;
	while (bytes > 0 && !contains_newline(*keep))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			ft_free_strs(&buf, keep, tmp);
			return ;
		}
		buf[bytes] = '\0';
		*tmp = ft_strdup(*keep);
		ft_free_strs(keep, 0, 0);
		*keep = ft_strjoin(*tmp, buf);
		ft_free_strs(tmp, 0, 0);
		if (!*keep)
			break ;
	}
	ft_free_strs(&buf, 0, 0);
} 