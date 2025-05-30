#include "push_swap.h"

void swap(t_stack *stk)
{
	t_stack *top;
	t_stack *new_top;

	top = stk->next;
	new_top = top->next;

	if (top == stk || new_top == stk)
		return ;

	stk->next = new_top;
	new_top->prev = stk;

	top->prev = new_top;
	top->next = new_top->next;

	new_top->next->prev = top;
	new_top->next = top;
}