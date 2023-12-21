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

int	main(int argc, char *argv[], char *env[])
{
	t_struct	p;

	init_struct(&p);
	error_check(argc, &p);
	split_envp_paths(&p, env);
	get_file_descriptors(&p, argc, argv);
	// command_processing(&p, argv[2]);
	// command_processing(&p, argv[3]);
	// if (pipe(p.fd) == -1)
	// 	(cleanup(&p, EXIT));
	// p.pid_first = fork();
	// if (p.pid_first == -1)
	// 	(cleanup(&p, EXIT));
	process_pipes(&p, argc, argv, env);
	cleanup(&p, EXIT);
}

//if infile doesnt exist, i get this error message with valgrind:
//Warning: invalid file descriptor -1 in syscall close()
