/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumattei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:32:09 by lumattei          #+#    #+#             */
/*   Updated: 2025/01/20 17:14:41 by lumattei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <unistd.h>

static void	reverse_rotate(t_stack_node **head)
{
	t_stack_node	*last_node;
	int	len;
	
	len = stack_len(*head);
	if (head == NULL || *head == NULL || len == 1)
		return ;
	last_node = find_last_node(*head);
	last_node->prev->next = NULL;
	(*head)->prev = last_node; 
	last_node->next = *head;
	last_node->prev = NULL;
	*head = last_node;
}

void	rra(t_stack_node **a, bool checker)
{
	reverse_rotate(a);
	if (!checker)
		write(1, "rra\n", 4);
}

void	rrb(t_stack_node **b, bool checker)
{
	reverse_rotate(b);
	if (!checker)
		write(1, "rrb\n", 4);
}

void rrr(t_stack_node **a, t_stack_node **b, bool checker)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (!checker)
		write(1, "rrr\n", 4);
}
/*
#include <stdio.h>

int	main(void)
{
	t_stack_node	**stack;
	stack == NULL;
	append_node(stack, 12);
	printf("%i\n", (*stack)->value);
}
*/
