/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-24 14:35:45 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-24 14:35:45 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	*gnl_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cs;
	unsigned char	*cd;

	if (!(dst || src))
		return (NULL);
	cs = (unsigned char *)src;
	cd = (unsigned char *)dst;
	if (dst > src)
	{
		while (len-- > 0)
			cd[len] = cs[len];
	}
	else
		while (len-- > 0)
			*cd++ = *cs++;
	return (dst);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\n')
		str[i++] = s2[j++];
	if (s2[j] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	if ((unsigned char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	i = 0;
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}

char	*appendbuff(char *str, char *buff)
{
	char	*apd;

	apd = gnl_strjoin(str, buff);
	if (str)
		free(str);
	if (gnl_strchr(buff, '\n'))
		gnl_memmove(buff, gnl_strchr(buff, '\n') + 1,
			ft_strlen(gnl_strchr(buff, '\n') + 1) + 1);
	else
		*buff = '\0';
	return (apd);
}

char	*get_next_line(int fd)
{
	static char	buff[10240][BUFFER_SIZE + 1u];
	char		*holder;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	holder = NULL;
	bytes = 0;
	while (!holder || !gnl_strchr(holder, '\n'))
	{
		if (!*buff[fd])
		{
			bytes = read(fd, buff[fd], BUFFER_SIZE);
			if (bytes == 0)
				return (holder);
			if (bytes < 0 && holder)
				free(holder);
			if (bytes < 0)
				return (NULL);
			buff[fd][bytes] = '\0';
		}
		holder = appendbuff(holder, buff[fd]);
	}
	return (holder);
}
