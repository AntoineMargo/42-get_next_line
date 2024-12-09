/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:19:38 by amargolo          #+#    #+#             */
/*   Updated: 2024/12/05 12:19:38 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = 0;
	src_len = 0;
	while (dest[dest_len])
		dest_len++;
	while (src[src_len])
		src_len++;
	if (dest_len >= dest_size)
		return (dest_size + src_len);
	while (src[i] && dest_len + i < dest_size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (0);
	if (start + len > s_len)
		len = s_len - start;
	string = malloc(len + 1);
	if (string == 0)
		return (0);
	ft_strlcpy(string, &s[start], len + 1);
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

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL)
        return malloc(new_size);

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    if (old_size > 0)
        memcpy(new_ptr, ptr, (old_size < new_size) ? old_size : new_size);

    free(ptr);

    return new_ptr;
}

