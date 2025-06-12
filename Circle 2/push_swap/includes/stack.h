/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:04:27 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/21 11:09:37 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H

# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"

# define STACK_H

typedef struct s_stack
{
	int	*stack;
	int	size;
	int	top;
	int	bottom;
}	t_stack;

typedef struct s_push_swap
{
	t_stack	a;
	t_stack	b;
	t_list	*op_list;
	bool	writing_mode;
}	t_ps;

enum	e_op
{
	null_op,
	pa,
	pb,
	ra,
	rb,
	rr,
	rra,
	rrb,
	rrr,
	sa,
	sb,
	ss
};

// data management
void		init_data(t_ps *data, int argc, char *argv[], bool flag);
void		init_stack(t_ps *data, t_stack *stk, int size);
bool		is_sorted(t_ps *data);
void		error(t_ps *data);
void		free_data(t_ps *data);

// operations
void		swap_a(t_ps *data);
void		swap_b(t_ps *data);

void		push_a(t_ps *data);
void		push_b(t_ps *data);

void		rotate_a(t_ps *data);
void		rotate_b(t_ps *data);
void		rotate_all(t_ps *data);

void		rotate_reverse_a(t_ps *data);
void		rotate_reverse_b(t_ps *data);
void		rotate_reverse_all(t_ps *data);

// operations utils
void		save_op(t_ps *data, enum e_op op);
void		print_ops(t_list *head);
const char	*op_to_string(enum e_op op);

// stack_utils.c
int			next_up(t_stack *stk, int index);
int			next_down(t_stack *stk, int index);
int			get_value(t_stack *stk, int index);
int			curr_size(t_stack *stk);
int			is_full(t_stack *stk);

// stack_init.c
void		fill_stack(t_ps *data, t_stack *stk, int size, char *argv[]);
bool		valid_arg(char *arg);

// op_utils.c
void		save_op(t_ps *data, enum e_op op);
void		print_ops(t_list *head);
const char	*op_to_string(enum e_op op);
enum e_op	op_from(t_list *node);

// free_split.c
void		free_split(char **splited);
int			valid_split(char **splited);

#endif
