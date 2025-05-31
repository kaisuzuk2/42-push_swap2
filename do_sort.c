#include "push_swap.h"



#include <stdio.h>



int get_stack_size(t_stack *stk);

static void do_rotate_both(t_cost *cst, t_stack *stk_a, t_stack *stk_b)
{
	while (cst->rr)
		(rotate(stk_a), rotate(stk_b), cst->rr--);
	while (cst->rrr)
		(reverse_rotate(stk_a), reverse_rotate(stk_b), cst->rrr--);
}

static void do_rotate(t_cost *cst, t_stack *stk_a, t_stack *stk_b)
{
	while (cst->ra)
		(rotate(stk_a), cst->ra--);
	while (cst->rb)
	{
		(rotate(stk_b), cst->rb--);
		printf("rotate b\n");
	}
	while (cst->rra)
		(reverse_rotate(stk_a), cst->rra--);
	while (cst->rrb)
		(reverse_rotate(stk_b), cst->rrb--);
}

void rotate_a(t_cost *cst, t_stack *stk_a)
{
	while (cst->ra)
		(rotate(stk_a), cst->ra--);
	while (cst->rra)
		(reverse_rotate(stk_a), cst->rra--);
}

void rotate_b(t_cost *cst, t_stack *stk_b)
{
	while (cst->rb)
		(rotate(stk_b), cst->rb--);
	while (cst->rrb)
		(reverse_rotate(stk_b), cst->rrb--);
}

void do_sort(t_stack *stk_a, t_stack *stk_b)
{
	int i;
	int total;
	t_cost *cst;

	total = get_stack_size(stk_a);
	i = 0;
	while (i < total)
	{
		cst = cost_utils(stk_a, stk_b);
		do_rotate_both(cst, stk_a, stk_b);
		rotate_a(cst, stk_a);
		rotate_b(cst, stk_b);
		push(stk_b, stk_a);
		// printf("===============\n");
		// t_stack *cur = stk_b->next;
		// while (cur != stk_b)
		// {
		// 	printf("%d ", cur->rank);
		// 	cur = cur->next;
		// }
		// printf("\n");
		// printf("===============\n");
		free(cst);
		i++;
	}
}

#include <stdio.h>
int main(void)
{
	int a[] = {1, 5, 2, 4, 3, 6, -7, -1, -10, -11, -12};
	t_stack *a_stack = stack_a_utils(a, 11);
	t_stack *b_stack = (t_stack *)malloc(sizeof(t_stack));
	b_stack->rank = -1;
	b_stack->next = b_stack;
	b_stack->prev = b_stack;
	do_sort(a_stack, b_stack);
	t_stack *cur = b_stack->next;
	// while (cur != b_stack)
	// {
	// 	printf("%d ", cur->rank);
	// 	cur = cur->next;
	// }
}