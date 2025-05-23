/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:33:25 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:33:25 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

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
