/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:51:54 by migonzal          #+#    #+#             */
/*   Updated: 2022/03/04 10:45:18 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./Libft/libft.h"

# define READ_END 0
# define WRITE_END 1


void error(void)
{
	perror(" A donde vas perro");
	exit (EXIT_FAILURE);
}

char *find_path(char *cmd, char **envp)
{
	char **paths;
	char *path;
	int	i;
	char *part_path;

	i = 0;

	while(ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;

	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}


void execute(char *argv, char **envp)
{
	char **cmd;

	cmd = ft_split(argv, ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
		error();
}


void child(char **argv, char ** envp, int *fd)
{
	int filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error();

	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void father(char **argv, char **envp, int *fd)
{
	int fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}


int main(int argc, char **argv, char **envp)
{
	int p[2];
	pid_t pid1;

	if (argc == 5)
	{
		if (pipe(p) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child(argv, envp, p);
		waitpid(pid1, NULL, 0);
		father(argv, envp, p);
	}


	else
	{
		ft_putstr_fd("Pero weno y esos argumentos?", 2);
	}
	return (0);
}

