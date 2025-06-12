/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:43:02 by dong-hki          #+#    #+#             */
/*   Updated: 2025/02/16 13:41:52 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	get_token(char **argv, t_token *data);
static int	error_token(t_token *data);

char	**tokenizer(const char *argv, int token_len)
{
	t_token	data;
	char	*p_argv;

	data.token = NULL;
	data.token_len = 0;
	p_argv = (char *)argv;
	data.token = ft_calloc(token_len + 1, sizeof(char *));
	if (!data.token)
	{
		perror("tokenizer ft_calloc error!");
		return (NULL);
	}
	while (*p_argv && data.token_len < token_len)
	{
		if (get_token(&p_argv, &data) == 0)
			return (NULL);
		++data.token_len;
	}
	return (data.token);
}

static int	get_token(char **argv, t_token *data)
{
	char	*buf;
	char	*start;
	int		quoted;
	size_t	buflen;

	quoted = 0;
	start = *argv;
	if (*start == SINGLE_QUOTE || *start == DOUBLE_QUOTE)
		quoted = 1;
	buflen = get_buflen(argv);
	if (quoted)
		buf = ft_substr(start, 1, buflen);
	else
		buf = ft_substr(start, 0, buflen);
	if (!buf)
		return (error_token(data));
	data->token[data->token_len] = ft_strdup(buf);
	if (!data->token[data->token_len])
		return (error_token(data));
	free(buf);
	return (1);
}

static int	error_token(t_token *data)
{
	size_t	i;

	i = 0;
	while (data->token[i])
		free(data->token[i++]);
	free(data->token);
	return (0);
}
