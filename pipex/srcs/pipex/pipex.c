/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:43:39 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/16 16:10:25 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_process(t_pipex *data, char **argv, char **envp, int *fd);
static void	second_process(t_pipex *data, char **argv, char **envp, int *fd);

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	t_pipex	data;

	if (argc != 5)
	{
		ft_putendl_fd("Error: Bad arguments", 2);
		return (EXIT_FAILURE);
	}
	init_data(&data, argv, envp, argc);
	if (pipe(pipefd) == -1)
		error(&data);
	first_process(&data, argv, envp, pipefd);
	++data.token_index;
	second_process(&data, argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
	free_data(&data);
	return (EXIT_SUCCESS);
}

static void	second_process(t_pipex *data, char **argv, char **envp, int *fd)
{
	int		outfile;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(data);
	if (pid == 0)
	{
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			error(data);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error(data);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			error(data);
		close(fd[1]);
		close(fd[0]);
		execute_cmd(data, data->tokenlist[1].path,
			data->tokenlist[1].token, envp);
	}
}

static void	first_process(t_pipex *data, char **argv, char **envp, int *fd)
{
	pid_t	pid;
	int		infile;

	pid = fork();
	if (pid == -1)
		error(data);
	if (pid == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			error(data);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error(data);
		if (dup2(infile, STDIN_FILENO) == -1)
			error(data);
		close(fd[0]);
		close(fd[1]);
		execute_cmd(data, data->tokenlist[0].path,
			data->tokenlist[0].token, envp);
	}
}
