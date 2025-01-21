/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:14:35 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/20 23:34:11 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_stack_node
{
	struct s_stack_node	*prev;
	struct s_stack_node	*next;
	struct s_stack_node	*target_node;
	int				value;
	int				current_position;
	int				push_price;
	bool				above_median;
	bool				cheapest;
}					t_stack_node;

// error_free.c

void	free_stack(t_stack_node **stack);
void	error_free(t_stack_node **a);
int	error_syntax(char *str_nbr);
int	error_repetition(t_stack_node	*a, int nbr);

// ft_split.c

char	**ft_split(char *str, char sp);

// stack_init.c

void	stack_init(t_stack_node **a, char **argv);

// stack_utils.c

void			append_node(t_stack_node **stack, int nbr);
t_stack_node	*find_last_node(t_stack_node *head);
t_stack_node	*find_smallest(t_stack_node	*stack);
t_stack_node	*return_cheapest(t_stack_node *stack);
int			stack_len(t_stack_node *stack);

// push_command.c

void	pa(t_stack_node **a, t_stack_node **b, bool checker);
void	pb(t_stack_node **b, t_stack_node **a, bool checker);

// rotate_command.c

void	ra(t_stack_node **a, bool checker);
void rb(t_stack_node **b, bool checker);
void	rr(t_stack_node **a, t_stack_node **b, bool checker);

// swap_command.c

void	sa(t_stack_node **a, bool checker);
void	sb(t_stack_node **b, bool checker);
void	ss(t_stack_node **a, t_stack_node **b, bool checker);

// reverse_rotate_command.c

void	rra(t_stack_node **a, bool checker);
void	rrb(t_stack_node **b, bool checker);
void rrr(t_stack_node **a, t_stack_node **b, bool checker);

//tiny_sort.c

bool	stack_sorted(t_stack_node *stack);
void	tiny_sort(t_stack_node **a);

# endif
