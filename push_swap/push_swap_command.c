/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:59:29 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/23 17:55:30 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	finish_rotation(t_stack_node **stack, t_stack_node *top_node, char	stack)
{
	while (*stack != top_node)
	{
		if (stack == 'a')
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra (stack, false);
		else if (stack == 'b')
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}
}




static void	reverse_rotate_both(t_stack_node **a, t_stack_node **b,
			t_stack_node *cheapest_node)
{
	while (*a != cheapest_node_target_node && *b != cheapest_node)
		rrr(a, b, false);
	set_current_position(*a);
	set_current_position(*b);
}

static void	rotate_both(t_stack_node **a, t_stack_node **b, 
			t_stack_node *cheapest_node)
{
	while (*a != cheapest_node_target_node && *b != cheapest_node)
		rr(a, b, false);
	set_current_position(*a);
	set_current_position(*b);
}

static void	move_nodes(t_stack_node **a, t_stack_node **b)
{
		t_stack_node	*cheapest_node;

		cheapest_node = return_cheapest(*b);
		if (cheapest_node->above_median && 
				cheapest_node->target_node->above_median)
			rotate_both(a, b, cheapest_node);
		else if (!(cheapest_node->above_median && 
					cheapest_node->target_node->above_median))
			reverse_rotate_both(a, b, cheapest_node);
		finish_rotation(*a, cheapest_node->target_node, 'a');
		finish_rotation(*b, cheapest_node, 'b');
		pa(a, b, false);
}

void	push_swap(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*smallest_node;
	int				len_a;

	len_a = len_stack(*a);
	if (len_a == 5)
		handle_five(a, b);
	else
		while (len_a-- > 3)
			pb(b, a, false);
	tiny_sort(a);
	while (*b)
	{
		init_node(*a, *b);
		move_nodes(a, b);
	}
	set_current_position(*a);
	smallest_node = find_smallest(*a);
	if (smallest_node->above median)
		while (*a != smallest_node)
			ra(*a, false);
	else
		while (*a != smallest_node)
			rra(a, false);
}

