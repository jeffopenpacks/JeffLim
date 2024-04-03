/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joolim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:28 by joolim            #+#    #+#             */
/*   Updated: 2023/11/27 18:58:30 by joolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct stack_list
{
	int					content;
	struct stack_list	*next;
	struct stack_list	*tgt;
	int					px;
	int					pos;
}	t_stack;

int			main(int argc, char **argv);
int			check_stack(t_stack **a, t_stack **b);
void		free_all(t_stack **a, t_stack **b, int flag);
t_stack		**make_list(t_stack **lst);
t_stack		*add_node(t_stack **lst);
t_stack		*smollest(t_stack **stacka);
int			reverse_node(t_stack **stack);
int			rotate_node(t_stack **stack);
int			swap_node(t_stack **stacka);
int			push_node(t_stack **stack1, t_stack **stack2);
int			read_stack(t_stack **lst, char **numarray);
int			rotate(t_stack **stacka, t_stack **stackb, char c);
int			move(t_stack **a, t_stack **b, char *str);
int			sort_three(t_stack **a, t_stack **b);
int			push(t_stack **stacka, t_stack **stackb, char c);
int			reverse(t_stack **stacka, t_stack **stackb, char c);
int			compare(t_stack *a, t_stack *b);
int			swap(t_stack **stacka, t_stack **stackb, char c);
int			solve4(t_stack **a, t_stack **b, int size);
int			check_data(t_stack **lst, char **numarray);
int			check_dup(t_stack **lst);
int			convert_int(t_stack **lst, char *numstr);
int			elegant_push(t_stack **a, t_stack **b);
void		update_pos(t_stack **a, t_stack **b);
void		set_tgt(t_stack **a, t_stack **b);
void		special_move_1(t_stack **a, t_stack **b, t_stack *cheapest);
void		special_move_2(t_stack **a, t_stack **b, t_stack *cheapest);
void		special_move_3(t_stack **a, t_stack **b, t_stack *cheapest);
void		special_move_4(t_stack **a, t_stack **b, t_stack *cheapest);
void		ps_lstadd_back(t_stack **lst, t_stack *new);
t_stack		*ps_lstlast(t_stack *lst);
int			ps_lstsize(t_stack *lst);
void		ps_lstclear(t_stack **lst, void (*del)(void*));
void		ps_lstadd_front(t_stack **lst, t_stack *new);
t_stack		*largest(t_stack **stacka);

#endif
