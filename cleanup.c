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
	if (p)
	{
		if (p->paths)
			ft_free_double_ptr(p->paths, p->path_amt, p);
		if (p->commands)
			ft_free_double_ptr(p->commands, p->com_amt, p);
		if (p->working_path)
			free (p->working_path);
	}
	if (status == EXIT)
		exit (EXIT_FAILURE);
}

void	ft_free_double_ptr(char **double_ptr, int amt, t_struct *p)
{
	int	i;

	i = amt;
	while (i >= 0)
	{
		if (double_ptr[i])
			free(double_ptr[i]);
		i--;
	}
	free(double_ptr);
}

void	free_commands(t_struct *p)
{
	int	i;

	i = 0;
	if (p->commands)
	{
		while (p->commands[i])
			free(p->commands[i++]);
		p->commands = NULL;
	}
	if (p->working_path)
		(free(p->working_path), p->working_path = NULL);
	p->com_amt = 0;
}
