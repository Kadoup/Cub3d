/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjourdan <tjourdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:36 by tjourdan          #+#    #+#             */
/*   Updated: 2025/09/09 17:52:14 by tjourdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dest;
	size_t	size;

	i = -1;
	j = -1;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	free((void *)s1);
	return (dest);
}

char	*read_buf(int fd, char	*buffer)
{
	char	*tmp;
	ssize_t	size;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	size = 1;
	while (!(ft_strchr(tmp, '\n')) && size != 0)
	{
		size = read(fd, tmp, BUFFER_SIZE);
		if (size < 0)
		{
			free(tmp);
			return (NULL);
		}
		tmp[size] = '\0';
		buffer = ft_strjoin(buffer, tmp);
	}
	free(tmp);
	return (buffer);
}

char	*keep_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_buffer(char *buffer)
{
	int		i;
	char	*nbuff;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	nbuff = malloc(ft_strlen(buffer) - i + 1);
	if (!nbuff)
	{
		free(nbuff);
		return (NULL);
	}
	while (buffer[i])
		nbuff[j++] = buffer[i++];
	nbuff[j] = '\0';
	free(buffer);
	return (nbuff);
}

char	*gnl(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_buf(fd, buffer);
	if (!buffer)
		return (NULL);
	line = keep_line(buffer);
	if (line)
		buffer = new_buffer(buffer);
	else if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
