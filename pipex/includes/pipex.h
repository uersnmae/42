/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:28:36 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/16 15:39:21 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include "tokenizer.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct s_pipex
{
	t_token	*tokenlist;
	int		token_size;
	int		token_index;
	int		token_base;
}	t_pipex;

// free_split.c
void	free_split(char **splited);

// cmd_get_pathname.c
char	*get_pathname(char *cmd_head, char **envp);

// cmd_execute.c
void	execute_cmd(t_pipex *data, char *path, char **token, char **envp);

// error.c
void	error(t_pipex *data);

// data_management.c
void	free_data(t_pipex *data);
void	init_data(t_pipex *data, char **argv, char **envp, int argc);

#endif
