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
	first_child(p, argc, argv, envp);
	waitpid(p->pid_first, NULL, 0);
	close(p->fd[1]);
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[0]);
	while (p->args > 2)
	{
		intermediate_child(p, argc, argv[i], envp);
		waitpid(p->pid_intermediate, NULL, 0);
		ft_close(p->fd[1], p->fd[0]);
		dup2(p->fd[0], STDIN_FILENO);
		close(p->fd[0]);
		p->args--;
		i++;
	}
	last_child(p, argc, argv, envp);
	waitpid(p->pid_last, NULL, 0);
	ft_close(p->outfile, p->fd[0]);
	close(p->fd[1]);
}

int	first_child(t_struct *p, int argc, char *argv[], char *envp[])
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
		dup2(p->fd[1], STDOUT_FILENO);
		ft_close(p->fd[1], p->outfile);
		if (command_processing(p, argv[2]) == 0)
			cleanup(p, EXIT);
		if (execv(p->working_path, p->commands) == -1)
			(cleanup(p, EXIT));
	}
	return (1);
}

int	last_child(t_struct *p, int argc, char *argv[], char *envp[])
{
	if (pipe(p->fd) == -1)
		(cleanup(p, EXIT));
	p->pid_last = fork();
	if (p->pid_last == -1)
		(cleanup(p, EXIT));
	if (p->pid_last != 0)
		return (0);
	free_commands(p);
	if (p->pid_last == 0)
	{
		close(p->fd[0]);
		dup2(p->outfile, STDOUT_FILENO);
		ft_close(p->outfile, p->fd[1]);
		if (command_processing(p, argv[argc - 2]) == 0)
			cleanup(p, EXIT);
		if (execv(p->working_path, p->commands) == -1)
			(cleanup(p, EXIT));
	}
	return (1);
}

int	intermediate_child(t_struct *p, int argc, char *str, char *envp[])
{
	if (pipe(p->fd) == -1)
		(cleanup(p, EXIT));
	p->pid_intermediate = fork();
	if (p->pid_intermediate == -1)
		(cleanup(p, EXIT));
	if (p->pid_intermediate != 0)
		return (0);
	free_commands(p);
	if (p->pid_intermediate == 0)
	{
		close(p->fd[0]);
		dup2(p->fd[1], STDOUT_FILENO);
		ft_close(p->fd[1], p->outfile);
		if (command_processing(p, str) == 0)
			cleanup(p, EXIT);
		if (execv(p->working_path, p->commands) == -1)
			(cleanup(p, EXIT));
	}
	return (1);
}
