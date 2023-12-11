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

int	main(int argc, char *argv[], char *envp[])
{
	t_struct	p;

	init_struct(&p);
	error_check(argc, argv, &p);
	split_envp_paths(&p, envp);
	get_file_descriptors(&p, argc, argv);
	process_pipes(&p, argc, argv, envp);
	close_files(p.infile, p.outfile);
	//printf("TASK PERFORMED!\n");
	cleanup(&p, EXIT);
}
