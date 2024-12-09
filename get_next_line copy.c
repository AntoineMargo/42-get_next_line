/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:49:35 by amargolo          #+#    #+#             */
/*   Updated: 2024/11/22 13:49:35 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>

#define BUFFER_SIZE 1024

static int	calc_total_len(char const *s1, char const *s2)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (s1[i])
		i++;
	total_len += i;
	i = 0;
	while (s2[i])
		i++;
	total_len += i;
	return (total_len);
}

static char	*ft_sstrcat(char *dest, char const *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		total_len;

	total_len = calc_total_len(s1, s2);
	string = malloc(total_len + 1);
	if (string == 0)
		return (0);
	ft_sstrcat(string, s1);
	ft_sstrcat(string, s2);
	string[total_len] = '\0';
	return (string);
}



char	*ft_strdup(char *src)
{
	int		len;
	char	*dup;

	len = 0;
	if (src == 0)
		return (0);
	while (src[len])
		len++;
	dup = malloc(len + 1);
	if (dup == 0)
		return (0);
	ft_strlcpy(dup, src, len + 1);
	return (dup);
}

static int find_new_line(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char *get_next_line(int fd)
{
	char	*buffer;
	ssize_t	chunk;
	int		new_line_i;
	char	*line;
	int		i;

	i = 0;
	new_line_i = -1;
	if (BUFFER_SIZE == 0 || fd < 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	while (new_line_i == -1)
	{
		chunk = read(fd, buffer, BUFFER_SIZE);
		if (chunk <= 0)
			return (0);
		buffer[chunk] = '\0';
		new_line_i = find_new_line(buffer);
		if (new_line_i != -1)
		{
			line = ft_substr(buffer, 0, new_line_i);
			return (line);
		}
		if (i == 0)
			line = ft_strdup(buffer);
		else
			line = ft_strjoin(line, buffer);
		i++;
	}
}

int main(void)
{
	int	fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0) {
		return (1);
	}
	line = get_next_line(fd);
	return (0);
}
