/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:17:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/16 15:23:46 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*stack_push(t_stack *tail, t_stack *element)
{
	t_stack	*head;

	head = malloc(sizeof(t_stack));
	if (!head)
		return (NULL);
	head->content = element->content;
	head->index = element->index;
	head->next = tail;
	return (head);
}

int	fill_stack(t_stack **a, t_args *args)
{
	t_stack	*new;
	int		i;

	i = args->size - 1;
	while (i >= 0)
	{
		new = new_stack(ft_atoi(args->array[i]));
		if (!new)
			return (0);
		new->next = *a;
		*a = new;
		i--;
	}
	return (1);
}

t_stack	*stack_pop(t_stack *stack)
{
	t_stack	*next;

	if (!stack)
		return (NULL);
	next = stack->next;
	free(stack);
	return (next);
}

void	stack_destroy(t_stack *head)
{
	if (!head)
		return ;
	stack_destroy(head->next);
	free(head);
}

t_stack	*new_stack(int content)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->content = content;
	new->index = -1;
	new->next = NULL;
	return (new);
}
