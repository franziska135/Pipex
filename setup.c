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

void	error_check(int argc, t_struct *p)
{
	p->args = argc - 3;
	if (argc < 5 || p->args < 2)
	{
		ft_write_error(ARGS, "no");
		cleanup(p, EXIT);
	}
}

void	get_file_descriptors(t_struct *p, int argc, char *argv[])
{
	p->infile = open(argv[1], O_RDONLY);
	if (p->infile < 0)
		(ft_write_error(OPEN, argv[1]));
	p->outfile = open(argv[argc - 1], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (p->outfile < 0)
		(ft_write_error(OPEN, argv[argc -1]));
}

void	ft_write_error(int status, char *str)
{
	write(2, "pipex: ", 7);
	if (status == OPEN)
	{
		write(2, "no such file or directory: ", 28);
		write(2, str, ft_strlen(str));
	}
	else if (status == ARGS)
		write(2, "invalid number of arguments!", 28);
	else if (status == COMMAND)
	{
		write(2, "command not found: ", 19);
		write(2, str, ft_strlen(str));
	}
	write(2, "\n", 1);
}

void	close_files(int infile, int outfile)
{
	close (infile);
	close (outfile);
}

void	init_struct(t_struct *p)
{
	p->working_path = NULL;
	p->paths = NULL;
	p->commands = NULL;
	p->path_amt = 0;
	p->com_amt = 0;
	p->flag = 0;
	p->args = 0;
	p->pid_first = 0;
	p->pid_last = 0;
	p->pid_intermediate = 0;
}
