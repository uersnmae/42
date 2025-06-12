/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 06:19:50 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/26 06:19:50 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char const *set, char c)
{
	char	*pset;

	pset = (char *)set;
	while (*pset)
	{
		if (*pset == c)
			return (1);
		pset++;
	}
	return (0);
}

char	*ft_strntrim(char const *s1, char const *set, size_t n)
{
	char	*ps1;
	char	*rps1;
	char	*trim;
	size_t	cpylen;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	ps1 = (char *)s1;
	rps1 = (char *)s1;
	i = 0;
	while (*rps1 && i++ < n)
		rps1++;
	i = 0;
	while ((ft_check_set(set, *ps1)) && i++ < n + 1)
		ps1++;
	cpylen = ft_strlen(ps1);
	while (rps1 > ps1 && cpylen > 0 && (ft_check_set(set, *(--rps1))))
		cpylen--;
	trim = (char *)ft_calloc(cpylen + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, ps1, cpylen + 1);
	return (trim);
}
