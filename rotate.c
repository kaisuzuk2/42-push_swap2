#include "push_swap.h"

void	rotate(t_stack *stk)
{
	t_stack *top;
	t_stack *tail;
	t_stack *new_top;

	top = stk->next;
	tail = stk->prev;
	new_top = top->next;

	if (new_top == stk || top == stk)
		return ;

	stk->next = new_top;
	new_top->prev = stk;

	tail->next = top;

	top->prev = tail;
	top->next = stk;
	stk->prev = top;
}

void reverse_rotate(t_stack *stk)
{
	t_stack *top;
	t_stack *tail;
	t_stack *new_tail;

	top = stk->next;
	tail = stk->prev;
	new_tail = tail->prev;

	if (new_tail == stk || tail == stk)
		return ;

	stk->next = tail;
	tail->prev = stk;

	tail->next = top;
	top->prev = tail;

	stk->prev = new_tail;
	new_tail->next = stk;
}