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

static char	**ft_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

static int	ft_amt_words(const char *s, char c)
{
	int	i;
	int	old_i;
	int	words;
	int	len;

	i = 0;
	words = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		while (i < len && s[i] == c)
			i++;
		old_i = i;
		while (i < len && s[i] != c)
			i++;
		if (i > old_i)
			words += 1;
	}
	return (words);
}

static size_t	ft_index(const char *s, char c, size_t i)
{
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c, int flag)
{
	char	**matrix;
	int		i;
	int		j;

	j = 0;
	i = 0;
	matrix = malloc((ft_amt_words(s, c) + 1) * sizeof(char *));
	if (!s || !matrix)
		return (NULL);
	while (j < ft_amt_words(s, c))
	{
		while (s[i] == c)
			i++;
		matrix[j] = ft_substr(s, i, ft_index(s, c, i) - i, flag);
		if (!matrix[j])
			return (ft_free(matrix));
		i = ft_index(s, c, i) + 1;
		j++;
	}
	matrix[j] = NULL;
	return (matrix);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (i == n || (s1[i] == '\0' && s2[i] == '\0'))
		return (0);
	else if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else
		return (0);
}
