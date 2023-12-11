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

int	command_processing(t_struct *p, char *str)
{
	free_commands(p);
	det_amt_split_commands(p, str);
	if (!p->working_path)
	{
		if (check_envp_paths(p, p->commands[0]) == 0)
			return (0);
	}
	return (1);
}

void	det_amt_split_commands(t_struct *p, char *arguments)
{
	int	i;

	i = 0;
	p->commands = ft_split(arguments, ' ', 0);
	if (!p->commands)
		cleanup(p, EXIT);
	while (p->commands[i])
	{
		p->com_amt++;
		i++;
	}
}

void	split_envp_paths(t_struct *p, char *envp[])
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 0;
	flag = 0;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 1)
	{
		p->paths = ft_split(envp[i], ':', 1);
		if (!p->paths)
			cleanup(p, EXIT);
	}
	count_paths(p);
	p->paths[0] = ft_strtrim(p->paths[0], "PATH=");
	if (!p->paths)
		cleanup(p, EXIT);
}

int	check_access(t_struct *p)
{
	int	error;

	if (access(p->working_path, F_OK) == 0
		&& access(p->working_path, X_OK) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	check_envp_paths(t_struct *p, char *str)
{
	int	i;
	int	flag;

	i = 0;
	p->working_path = ft_strjoin(p->commands[0], "");
	if (check_access(p) == FALSE)
		(free(p->working_path), p->working_path = NULL);
	else
		return (1);
	while (p->paths[i])
	{
		p->working_path = ft_strjoin(p->paths[i], str);
		if (!p->working_path)
			cleanup(p, EXIT);
		if (check_access(p) == TRUE)
			return (1);
		i++;
		free(p->working_path);
		p->working_path = NULL;
	}
	ft_write_error(COMMAND, p->commands[0]);
	return (0);
}
