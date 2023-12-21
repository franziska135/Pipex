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

char	**ft_free(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
	return (NULL);
}

int	ft_amt_words(const char *s, char c)
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

	matrix = NULL;
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
			return (ft_free(matrix), NULL);
		i = ft_index(s, c, i) + 1;
		j++;
	}
	matrix[j] = NULL;
	return (matrix);
}

