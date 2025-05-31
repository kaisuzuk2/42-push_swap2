#include "push_swap.h"

static void cost_init(t_cost *cst)
{
	cst->rr = 0;
	cst->rrr = 0;
	cst->ra = 0;
	cst->rb = 0;
	cst->rra = 0;
	cst->rrb = 0;
}

static int get_total_cost(t_cost *cst)
{
	return (cst->rr + cst->rrr + cst->ra + cst->rb + cst->rra + cst->rrb);
}

static int get_stack_size(t_stack *stk)
{
	int count;
	t_stack *cur;

	count = 0;
	cur = stk->next;
	while (cur != stk)
	{
		cur = cur->next;
		count++;
	}
	return (count);
}

static void calc_b_cost(t_cost *cst, t_stack *stk_b, int rank)
{
	int i;
	t_stack *cur;
	t_stack *top;
	t_stack *tail;

	i = 0;
	cur = stk_b->next;
	top = cur;
	tail = stk_b->prev;
	if (cur == stk_b)
		return ;
	if (top->rank < rank)
	{
		cst->rrb = get_stack_size(stk_b);
		return ;
	}
	while (cur != stk_b)
	{
		if (cur->rank > rank && cur->next->rank < rank)
			break;
		i++;
		cur = cur->next;
	}
		cst->rb = i;
		cst->rrb = get_stack_size(stk_b) - i;
}

static void optimization(t_cost *cst)
{
	while (cst->ra && cst->rb)
		(cst->ra--, cst->rb--, cst->rr++);
	while (cst->rra && cst->rrb)
		(cst->rra--, cst->rrb--, cst->rrr++);
	if (cst->ra + cst->rb + cst->rr >= cst->rra + cst->rrb + cst->rrr)
		(cst->rra = 0, cst->rrb = 0, cst->rrr = 0);
	else
		(cst->ra = 0, cst->rb = 0, cst->rr = 0);
}

t_cost *cost_utils(t_stack *stk_a, t_stack *stk_b)
{
	t_cost *cur_cst;
	t_cost *best_cst;
	t_stack *cur;
	int i;

	best_cst = NULL;
	cur = stk_a->next;
	i = 0;
	while (cur != stk_a)
	{
		cur_cst = (t_cost *)malloc(sizeof(t_cost));
		if (!cur_cst)
			return (NULL);
		cost_init(cur_cst);
		calc_b_cost(cur_cst, stk_b, cur->rank);
		cur_cst->ra = i;
		cur_cst->rra = get_stack_size(stk_a) - i;
		optimization(cur_cst);
		if (!best_cst || get_total_cost(cur_cst) < get_total_cost(best_cst))
		{
			if (best_cst)
				free(best_cst);
			best_cst = cur_cst;
		}
		else
			free(cur_cst);
		cur = cur->next;
		i++;
	}
	return (best_cst)
}