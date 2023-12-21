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

void	count_paths(t_struct *p)
{
	int	i;

	i = 0;
	p->path_amt = 0;
	while (p->paths[i])
	{
		p->path_amt++;
		i++;
	}
}

void	ft_close(t_struct *p, int firstfile, int secondfile)
{
	if (close(firstfile) == -1)
		cleanup(p, EXIT);
	if (close(secondfile) == -1)
		cleanup(p, EXIT);
}

size_t	ft_strlen(const char *s)
{
	int		i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		return (i);
	}
	return (0);
}
