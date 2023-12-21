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

#ifndef PIPEX_H
# define PIPEX_H

# define TRUE 1
# define FALSE 0
# define NONE 100
# define NO_EX 0
# define EXIT 1
# define OPEN 1
# define COMMAND 2
# define ARGS 3
# define SMALL 0
# define BIG 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_struct
{
	char	**paths;
	char	**commands;
	int		com_amt;
	int		path_amt;
	char	*working_path;
	int		flag;
	int		infile;
	int		outfile;
	int		pid_first;
	int		pid_last;
	int		pid_intermediate;
	int		fd[2];
	int		args;
}	t_struct;

//setup
int				main(int argc, char *argv[], char *envp[]);
void			error_check(int argc, t_struct *p);
int				find_amount_args(int argc, char *argv[]);
void			close_files(int infile, int outfile);
void			init_struct(t_struct *p);
void			split_envp_paths(t_struct *p, char *envp[]);
void			count_paths(t_struct *p);
int				command_processing(t_struct *p, char *str);
void			init_struct(t_struct *p);
int				check_envp_paths(t_struct *p, char *str);
int				det_amt_split_commands(t_struct *p, char *arguments);
void			free_commands(t_struct *p);
int				first_child(t_struct *p, char *envp[]);
void			process_pipes(t_struct *p, int ac, char *av[], char *envp[]);
void			ft_write_error(int status, char *str);
void			get_file_descriptors(t_struct *p, int argc, char *argv[]);
void			ft_close(t_struct *p, int firstfile, int secondfile);
//run
void			access_paths(t_struct *p, char *str);
char			*ft_strjoin(char *s1, char *s2);
int				check_access(t_struct *p);
int				check_child_pid(int child_pid, t_struct *p);
int				intermediate_child(t_struct *p, char *ep[]);
int				last_child(t_struct *p, char *envp[]);
//cleanup
void			cleanup(t_struct *p, int status);
void			ft_free_double_ptr(char **double_ptr, int amt);

//libft
char			**ft_split(char *s, char c, int flag);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_substr(char *s, unsigned int start, size_t len, int flag);
char			*ft_strdup(const char *s);
char			*ft_strtrim(char *s1, char const *set);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char *s, unsigned int start, size_t len, int flag);
char			*ft_strtrim(char *s1, char const *set);
char			*ft_strjoin(char *s1, char *s2);
#endif