/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:56:25 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/16 15:24:57 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "tokenizer.h"

static void	get_token(t_pipex *data, char **argv, char **envp);

void	free_data(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->token_size)
	{
		if (data->tokenlist[i].token)
			free_split(data->tokenlist[i].token);
		if (data->tokenlist[i].path)
			free(data->tokenlist[i].path);
		i++;
	}
	free(data->tokenlist);
	exit(EXIT_FAILURE);
}

void	init_data(t_pipex *data, char **argv, char **envp, int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data->token_size = argc - 4;
		data->token_base = 3;
	}
	else
	{
		data->token_size = argc - 3;
		data->token_base = 2;
	}
	data->tokenlist = ft_calloc(data->token_size, sizeof(t_token));
	if (!data->tokenlist)
	{
		ft_putendl_fd("Data initialize error!", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	get_token(data, argv, envp);
	data->token_index = 0;
}

static void	get_token(t_pipex *data, char **argv, char **envp)
{
	int	i;
	int	token_len;

	i = 0;
	while (i < data->token_size)
	{
		token_len = token_count(argv[data->token_base + i]);
		data->tokenlist[i].token = \
			tokenizer(argv[data->token_base + i], token_len);
		if (!data->tokenlist[i].token)
		{
			ft_putendl_fd("Error mallocating tokenlist[i]", STDERR_FILENO);
			free_data(data);
		}
		data->tokenlist[i].path = \
			get_pathname(data->tokenlist[i].token[0], envp);
		if (!data->tokenlist[i].path)
		{
			ft_putendl_fd("Wrong command", STDERR_FILENO);
			free_data(data);
		}
		i++;
	}
}
