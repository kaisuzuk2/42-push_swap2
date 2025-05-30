#include "push_swap.h"

void push(t_stack *to_stack, t_stack *from_stack)
{
	t_stack *node;
	t_stack *top;

	node = from_stack->next;
	top = to_stack->next;
	if (node == from_stack)
		return ;

	from_stack->next = node->next;
	node->next->prev = from_stack;
	if (top == to_stack)
	{
		to_stack->next = node;
		to_stack->prev = node;
		node->prev = to_stack;
		node->next = to_stack;
		return ;
	}
	node->prev = to_stack;
	node->next = top;
	
	top->prev = node;

	to_stack->next = node;
}