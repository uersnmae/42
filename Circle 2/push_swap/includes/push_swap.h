/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:26:53 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/21 11:09:01 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H

# include "stack.h"

# define PUSH_SWAP_H

enum	e_loc
{
	TOP_A,
	BOTTOM_A,
	TOP_B,
	BOTTOM_B,
};

typedef struct s_chunk
{
	enum e_loc	loc;
	int			size;

}	t_chunk;

typedef struct s_split_dest
{
	t_chunk	min;
	t_chunk	mid;
	t_chunk	max;
}	t_split_dest;

// sort
void		sort(t_ps *data);
void		sort_two(t_ps *data, t_chunk *to_sort);
void		sort_one(t_ps *data, t_chunk *to_sort);
void		sort_three(t_ps *data, t_chunk *to_sort);

// chunk_sort.c
void		chunk_sort(t_ps *data);
void		rec_chunk_sort(t_ps *data, t_chunk *to_sort);

// chunk_split.c
void		init_size(t_chunk *min, t_chunk *mid, t_chunk *max);
void		set_split_loc(enum e_loc loc, t_chunk *min,
				t_chunk *mid, t_chunk *max);
void		set_third_pivot(int size, int *pivot_1, int *pivot_2);
void		chunk_split(t_ps *data, t_chunk *to_split, t_split_dest *dest);

// chunk_utils.c
int			chunk_value(t_ps *data, t_chunk *chunk, int n);
int			chunk_max_value(t_ps *data, t_chunk *chunk);
t_stack		*loc_to_stack(t_ps *data, enum e_loc loc);

// move.c
int			move_from_to(t_ps *data, enum e_loc from, enum e_loc to);

// opti_to_top.c
void		chunk_to_top(t_ps *data, t_chunk *to_sort);

// opti_sort_asap.c
void		split_max_reduction(t_ps *data, t_chunk *max);
bool		a_partly_sort(t_ps *data, int from);

// opti_post_sort.c
void		post_sort_optimization(t_ps *data);

// opti_post_sort_utils.c
enum e_op	neutral_op(enum e_op op);
bool		op_on_same_stack(enum e_op ref, enum e_op to_check);
enum e_op	child_op(enum e_op first, enum e_op second);
void		remove_op(t_list *to_delete);

// sort.c
void		sort(t_ps *data);

// easy_sort.c
void		easy_sort(t_ps *data, t_chunk *to_sort);

#endif
