/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:19 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/09 16:28:26 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void	save_op(t_ps *data, enum e_op op)
{
	t_list	*new;

	new = ft_lstnew((void *)(uintptr_t)op);
	if (!new)
		error(data);
	ft_lstadd_back(&data->op_list, new);
}

void	print_ops(t_list *head)
{
	t_list	*curr;

	curr = head;
	while (curr)
	{
		ft_printf("%s\n", op_to_string(op_from(curr)));
		curr = curr->next;
	}
}

const char	*op_to_string(enum e_op op)
{
	static const char	*op_string[12] = {
		"null_op",
		"pa",
		"pb",
		"ra",
		"rb",
		"rr",
		"rra",
		"rrb",
		"rrr",
		"sa",
		"sb",
		"ss"
	};

	return (op_string[op]);
}

enum e_op	op_from(t_list *node)
{
	return ((enum e_op)(uintptr_t)node->content);
}
