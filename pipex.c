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

void	print_commands(t_struct *p, int argc, char *argv[])
{
	int j = 2;
	while (j <= argc - 2)
	{
	command_processing(p, argv[j]);
	int i = 0;
		while (p->commands[i])
		{
			printf("command %d\t%s\n", i, p->commands[i]);
			printf("strlen:\t%zu\n", ft_strlen(p->commands[i]));
			i++;
		}
		printf("working path:\t%s\n", p->working_path);
		j++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_struct	p;
	
	init_struct(&p);
	error_check(argc, &p);
	split_envp_paths(&p, env);
	//command_processing(&p, argv[2]);
	//print_commands(&p, argc, argv);
	get_file_descriptors(&p, argc, argv);
	process_pipes(&p, argc, argv, env);
	// close_files(p.infile, p.outfile);
	//printf("TASK PERFORMED!\n");
	cleanup(&p, EXIT);
}
