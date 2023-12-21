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

void	process_pipes(t_struct *p, int argc, char *argv[], char *envp[])
{
	int	i;

	i = 3;
	if (command_processing(p, argv[2]) == 0)
		cleanup(p, EXIT);
	first_child(p, envp);
	dup2(p->fd[0], STDIN_FILENO);
	ft_close(p, p->fd[0], p->fd[1]);
	while (p->args > 2)
	{
		if (command_processing(p, argv[i]) == 0)
			cleanup(p, EXIT);
		intermediate_child(p, envp);
		dup2(p->fd[0], STDIN_FILENO);
		ft_close(p, p->fd[0], p->fd[1]);
		p->args--;
		i++;
	}
	if (command_processing(p, argv[argc - 2]) == 0)
			cleanup(p, EXIT);
	last_child(p, envp);
	ft_close(p, p->outfile, p->fd[0]);
	close(p->fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (waitpid(p->pid_intermediate, NULL, 0) == -1)
		cleanup(p, EXIT);
	if (waitpid(p->pid_first, NULL, 0) == -1)
		cleanup(p, EXIT);
	if (waitpid(p->pid_last, NULL, 0) == -1)
		cleanup(p, EXIT);
}

int	first_child(t_struct *p, char *envp[])
{
	if (pipe(p->fd) == -1)
		(cleanup(p, EXIT));
	dup2(p->infile, STDIN_FILENO);
	close(p->infile);
	p->pid_first = fork();
	if (p->pid_first == -1)
		(cleanup(p, EXIT));
	if (p->pid_first != 0)
		return (0);
	if (p->pid_first == 0)
	{
		close(p->fd[0]);
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			(ft_close(p, p->fd[1], p->outfile), cleanup(p, EXIT));
		ft_close(p, p->fd[1], p->outfile);
		if (p->infile > 0)
		{
			if (execve(p->working_path, p->commands, envp) == -1)
				(cleanup(p, EXIT));
		}
		cleanup(p, EXIT);
	}
	return (1);
}

int	last_child(t_struct *p, char *envp[])
{
	if (pipe(p->fd) == -1)
		(cleanup(p, EXIT));
	p->pid_last = fork();
	if (p->pid_last == -1)
		(cleanup(p, EXIT));
	if (p->pid_last != 0)
		return (0);
	if (p->pid_last == 0)
	{
		close(p->fd[0]);
		dup2(p->outfile, STDOUT_FILENO);
		ft_close(p, p->outfile, p->fd[1]);
		if (p->outfile > 0)
		{
			if (execve(p->working_path, p->commands, envp) == -1)
				(cleanup(p, EXIT));
		}
		cleanup(p, EXIT);
	}
	return (1);
}

int	intermediate_child(t_struct *p, char *envp[])
{
	if (pipe(p->fd) == -1)
		(cleanup(p, EXIT));
	p->pid_intermediate = fork();
	if (p->pid_intermediate == -1)
		(cleanup(p, EXIT));
	if (p->pid_intermediate != 0)
		return (0);
	if (p->pid_intermediate == 0)
	{
		close(p->fd[0]);
		dup2(p->fd[1], STDOUT_FILENO);
		ft_close(p, p->fd[1], p->outfile);
		if (p->fd[0] > 0)
		{
			if (execve(p->working_path, p->commands, envp) == -1)
				cleanup(p, EXIT);
		}
		cleanup(p, EXIT);
	}
	return (1);
}
