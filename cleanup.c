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

void	cleanup(t_struct *p, int status)
{
	if (p != NULL)
	{
		if (p->paths != NULL)
			ft_free_double_ptr(p->paths, p->path_amt);
		if (p->commands != NULL)
			ft_free_double_ptr(p->commands, p->com_amt);
		if (p->working_path != NULL)
			free (p->working_path);
	}
	if (status == EXIT)
		exit (EXIT_FAILURE);
}

void	ft_free_double_ptr(char **double_ptr, int amt)
{
	int	i;

	i = amt;
	while (i >= 0)
	{
		if (double_ptr[i] != NULL)
			free(double_ptr[i]);
		i--;
	}
	free(double_ptr);
}

void	free_commands(t_struct *p)
{
	int	i;

	i = 0;
	if (p->commands != NULL)
	{
		while (p->commands[i] != NULL)
			free(p->commands[i++]);
		p->commands = NULL;
	}
	if (p->working_path != NULL)
		(free(p->working_path), p->working_path = NULL);
	p->com_amt = 0;
}
