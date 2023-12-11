/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarggra <fmarggra@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:18:27 by fmarggra          #+#    #+#             */
/*   Updated: 2023/12/05 15:18:29 by fmarggra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char *s, unsigned int start, size_t len, int flag)
{
	unsigned int	i;
	char			*p_string;
	size_t			length;

	i = 0;
	length = 0;
	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	if (len < length)
		length = len;
	p_string = (char *)malloc(sizeof(char) * (length + 1 + flag));
	if (p_string == NULL)
		return (NULL);
	while (i < length && s[start + i] != '\0')
	{
		p_string[i] = s[start + i];
		i++;
	}
	if (flag == 1)
		p_string[i] = '/';
	p_string[i + flag] = '\0';
	return (p_string);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*p_newstr;

	i = 0;
	while (s[i] != '\0')
		i++;
	p_newstr = (char *)malloc((i + 1) * sizeof(char));
	if (p_newstr == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		p_newstr[i] = s[i];
		i++;
	}
	p_newstr[i] = '\0';
	return (p_newstr);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;
	int		size;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > 0 && ft_strchr(set, s1[end]))
		end--;
	size = end - start + 1;
	if (start > end)
		size = 1;
	result = (ft_substr(s1, start, (size), 0));
	if (!result)
		return (free(s1), NULL);
	free(s1);
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		total_size;
	char	*newstr;

	i = 0;
	j = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc(total_size + 1);
	if (newstr == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}
