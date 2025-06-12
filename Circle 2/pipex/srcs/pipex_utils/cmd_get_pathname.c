/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_pathname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:08:16 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/16 15:09:27 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **envp)
{
	int		i;
	bool	flag;
	char	*path;

	i = 0;
	flag = false;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			flag = true;
		if (flag)
			break ;
		++i;
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	if (!path || !flag)
	{
		perror("get_path error");
		if (!path)
			free(path);
		exit(EXIT_FAILURE);
	}
	return (path);
}

static bool	valid_path(char *path)
{
	if (access(path, X_OK) != -1)
		return (true);
	return (false);
}

static char	*add_slash(char *str, char *cmd_head)
{
	char	*temp;
	char	*pathname;

	temp = ft_strjoin(str, "/");
	if (!temp)
		return (NULL);
	pathname = ft_strjoin(temp, cmd_head);
	free(temp);
	if (!pathname)
		return (NULL);
	return (pathname);
}

char	*get_pathname(char *cmd_head, char **envp)
{
	char	*fullpath;
	char	**splitpath;
	size_t	i;

	fullpath = get_path(envp);
	splitpath = ft_split(fullpath, ':');
	free(fullpath);
	i = 0;
	while (splitpath[i])
	{
		fullpath = add_slash(splitpath[i++], cmd_head);
		if (!fullpath)
			break ;
		if (valid_path(fullpath))
		{
			free_split(splitpath);
			return (fullpath);
		}
		free(fullpath);
	}
	free_split(splitpath);
	return (NULL);
}
