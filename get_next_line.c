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
#include <unistd.h>

#define BUFFER_SIZE 42

void	ft_bzero(void *area, int n)
{
	char	*target;

	target = (char *)area;
	while (n > 0)
	{
		*target = 0;
		target++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	size_t	total_size;

	total_size = size * count;
	array = malloc(total_size);
	if (array == 0)
		return (0);
	ft_bzero(array, total_size);
	return (array);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;

	i = 0;
	if (dest_size == 0)
		return (0);
	while (i < dest_size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

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
	string = ft_calloc(total_len + 1, sizeof(char));
	if (string == 0)
		return (0);
	ft_sstrcat(string, s1);
	ft_sstrcat(string, s2);
	string[total_len] = '\0';
	return (string);
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


char	*ft_strdup(char *src)
{
	int		len;
	char	*dup;

	len = 0;
	if (src == 0)
		return (0);
	while (src[len])
		len++;
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup == 0)
		return (0);
	ft_strlcpy(dup, src, len + 1);
	return (dup);
}

char	*ft_strdup_ltd(char *src, int limit)
{
	char	*dup;

	if (src == 0)
		return (0);
	dup = ft_calloc(limit + 1, sizeof(char));
	if (dup == 0)
		return (0);
	ft_strlcpy(dup, src, limit + 1);
	return (dup);
}


int	add_buffer_to_hold(char **hold, char *buffer)
{
	char	*temp;

	if (*hold)
	{
		temp = ft_strjoin(*hold, buffer);
		if (!temp)
			return (0);
		free(*hold);
		*hold = temp;
	}
	else
	{
		*hold = ft_strdup(buffer);
		if (!*hold)
			return (0);
	}
	return (1);
}

int	extract_data_from_fd(int fd, char **hold)
{
	int	bytes_read;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		add_buffer_to_hold(hold, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (1);
}

char *extract_last_line_from_hold(char **hold)
{
	char	*newline_pos;
	char	*line;
	char	*temp_hold;
	int		line_len;
	
	newline_pos = 0;
	newline_pos = ft_strchr(*hold, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - *hold + 1;
		line = ft_strdup_ltd(*hold, line_len);
		temp_hold = ft_strdup(newline_pos + 1);
		free(*hold);
		*hold = temp_hold;
	}
	else
	{
		line = ft_strdup(*hold);
		free(*hold);
		*hold = 0;
	}
	return line;
}

char *get_next_line(int fd)
{
	static char	*hold;
	char		*line;

	line = 0;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	extract_data_from_fd(fd, &hold);
	if (hold)
		line = extract_last_line_from_hold(&hold);

	// printf("hold: %s", hold);
	// printf("\n");
	// printf("line: %s", line);
	// printf("\n");

	return (line);
}

int main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0) {
		return (1);
	}
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
	return (0);
}
