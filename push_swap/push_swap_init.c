/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <lumattei@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:39:31 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/22 19:58:42 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_current_position(t_stack_node *stack)
{
	int	i;
	int	centerline;

	i = 0;
	if (NULL == stack)
		return ;
	centerline = stack_len(stack) / 2;
	while (stack)
	{
		stack->current_position = i;
		if (i > centerline)
			stack->above_median = false;
		else
			stack->above_median = true;
		stack = stack->next;
		i++;
	}
}

static void	set_target_node(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*target_node;
	t_stack_node	*current_a;
	long			target_index;

	while (b)
	{
		target_index = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value && current_a->value < target_index)
				{
					target_index = current_a->value;
					target_node = current_a;
				}
			current_a = current_a->next;
		}
		if (target_index = LONG_MAX)
			b->target_node = find_smallest(a);
		else
			b->target_node = target_node;
		b = b->next;
	}
}

static void	push_price(t_static_node *a, t_static_node *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (b)
	{
		b->push_price = b->current_position;
		if (!(b->above_median))
			b->push_price = b_len - b->current_position;
		if (b->target_node->above_median)
			b->push_price += b->target_node->current_position;
		else
			b->push_price += (a_len - b->target_node->current_position);
		b = b->next;
	}
}

void	set_cheapest(t_stack_node *b)
{
	long			cheapest_value;
	t_stack_node	*cheapest_node;

	if (NULL == b)
		return ;
	cheapest_value = LONG_MAX;
	while (b)
	{
		if (b->push_price < cheapest_value)
		{
			cheapest_value = b->push_price;
			cheapest_node = b;
		}
		b = b->next;
	}
	cheapest_node->cheapest = true;
}

void	init_nodes(t_stack_node *a, t_stack_node *b)
{
	set_current_position(a);
	set_current_position(b);
	set_target_node(a, b);
	set_price(a, b);
	set_cheapest(b);
}
