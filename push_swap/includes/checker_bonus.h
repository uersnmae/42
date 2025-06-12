/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:56:23 by dong-hki          #+#    #+#             */
/*   Updated: 2025/01/21 11:09:16 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "stack.h"
# include "get_next_line.h"

// do_operations.c
enum e_op	string_to_op(char *str);
void		read_ops(t_ps *data);

// checker_gnl_bonus.c
char		*get_next_line_ps(int fd);

#endif
