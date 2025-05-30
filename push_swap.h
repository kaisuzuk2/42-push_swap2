#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>

typedef struct s_stack
{
	int				rank;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

void				rotate(t_stack *stk);
void				reverse_rotate(t_stack *stk);
void				swap(t_stack *stk);
void push(t_stack *to_stack, t_stack *from_stack);

#endif