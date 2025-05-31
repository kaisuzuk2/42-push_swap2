#include "push_swap.h"



#include <stdio.h>


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

int get_stack_size(t_stack *stk)
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
	t_stack *cur;
	t_stack *max;
	t_stack *min;
	int i;

	if (stk_b->next == stk_b)
		return ;
	cur = stk_b->next;
	
	max = cur;
	min = cur;
	while (cur != stk_b)
	{
		if (cur->rank < min->rank)
			min = cur;
		if (cur->rank > max->rank)	
			max = cur;
		cur = cur->next;
	}
	cur = stk_b->next;
	i = 0;
	if (rank > max->rank)
	{
		while (cur != stk_b)
		{
			if (cur->rank == max->rank)
			{
				cst->rb = i;
				cst->rrb = get_stack_size(stk_b) - i;
				return ;
			}
			i++;
			cur = cur->next;
		}
		return ;
	}
	i = 1;
	if (rank < min->rank)
	{ 
		while (cur != stk_b)
		{
			if (cur->rank == min->rank)
			{
				cst->rb = i;
				cst->rrb = get_stack_size(stk_b) - i;
				return ;
			}
			i++;
			cur = cur->next;
		}
		return ;
	}
	i = 1;
	while (cur != stk_b)
	{
		if (cur->rank > rank && cur->next->rank < rank)
			break;
		cur = cur->next;
		i++;
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
	if ((cst->ra + cst->rb + cst->rr) <= (cst->rra + cst->rrb + cst->rrr))
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
			best_cst = (t_cost *)malloc(sizeof(t_cost));
			*best_cst = *cur_cst;
		}
		else
			free(cur_cst);
		cur = cur->next;
		i++;
	}
	// printf("bestcost\n");
	// printf("rr = %d, rrr = %d, ra = %d, rb = %d, rra = %d, rrb = %d\n", best_cst->rr, best_cst->rrr, best_cst->ra, best_cst->rb, best_cst->rra, best_cst->rrb);
	return (best_cst);
}