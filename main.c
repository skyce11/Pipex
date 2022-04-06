/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:26:35 by migonzal          #+#    #+#             */
/*   Updated: 2022/04/06 11:24:57 by migonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		p[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(p) == -1)
			error();
		pid1 = fork();
		if (pid1 == 0)
			child(argv, envp, p);
		waitpid(pid1, NULL, 0);
		father(argv, envp, p);
	}
	else
		ft_putstr_fd("Pero weno y esos argumetos?", 2);
	return (0);
}
