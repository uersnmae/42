/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:26:36 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/16 15:35:59 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	openfile(t_pipex *data, char *filename, enum e_mode mode);
static void	child_process(t_pipex *data, char **envp, int i);
static void	last_child(t_pipex *data, char **envp, int fd, int i);
static void	not_here_doc(t_pipex *data, char **argv, int *files, int argc);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		i;
	int		files[2];

	if (argc >= 5 && (ft_strncmp(argv[1], "here_doc", 8) || argc >= 6))
	{
		init_data(&data, argv, envp, argc);
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			files[1] = openfile(&data, argv[argc - 1], w);
			here_doc(&data, argv[2]);
		}
		else
			not_here_doc(&data, argv, files, argc);
		i = 0;
		while (i < data.token_size - 1)
			child_process(&data, envp, i++);
		last_child(&data, envp, files[1], i);
		while (wait(NULL) > 0)
			;
		free_data(&data);
		return (EXIT_SUCCESS);
	}
	ft_putendl_fd("Bad arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	not_here_doc(t_pipex *data, char **argv, int *files, int argc)
{
	files[0] = openfile(data, argv[1], r);
	files[1] = openfile(data, argv[argc - 1], w);
	if (dup2(files[0], STDIN_FILENO) == -1)
		error(data);
	close(files[0]);
}

static int	openfile(t_pipex *data, char *filename, enum e_mode mode)
{
	int	fd;

	if (mode == w)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
		error(data);
	return (fd);
}

static void	last_child(t_pipex *data, char **envp, int fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(data);
	if (pid == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			error(data);
		close(fd);
		execute_cmd(data, data->tokenlist[i].path,
			data->tokenlist[i].token, envp);
	}
}

static void	child_process(t_pipex *data, char **envp, int i)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error(data);
	pid = fork();
	if (pid == -1)
		error(data);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			error(data);
		close(pipefd[1]);
		execute_cmd(data, data->tokenlist[i].path,
			data->tokenlist[i].token, envp);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			error(data);
		close(pipefd[0]);
	}
}
