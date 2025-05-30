#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

typedef struct s_stack
{
	int				rank;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

typedef struct s_cost 
{
	int rr;
	int rrr;
	int ra;
	int rb;
	int rra;
	int rrb;
} t_cost;

void				rotate(t_stack *stk);
void				reverse_rotate(t_stack *stk);
void				swap(t_stack *stk);
void push(t_stack *to_stack, t_stack *from_stack);

t_stack *stack_a_utils(int *arr, int size);
t_cost *cost_utils(t_stack *stk_a, t_stack *stk_b);

#endif