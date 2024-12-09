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

#define BUFFER_SIZE 42

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

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

// static int find_newline(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\n')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

void	add_buffer_to_text(char **text, char *buffer)
{
	char	*temp;
	char	*string;

	if (*text)
	{
		temp = ft_strjoin(*text, buffer);
		free(*text);
		*text = temp;
	}
	else
		*text = ft_strdup(buffer);
}

void	extract_text_from_fd(int fd, char **text)
{
	ssize_t	bytes_read;
	char	*buffer;
	int		new_line_i;

	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		add_buffer_to_text(text, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
}

char *extract_last_line_from_text()
{
	static int start;
	static int end;


}

char *get_next_line(int fd)
{
	static char	*text;
	char	*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	extract_text_from_fd(fd, &text);
	line = extract_last_line_from_text();
	return (text);
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
