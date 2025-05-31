#include "push_swap.h"

static void stack_a_init(t_stack *stk_a)
{
	stk_a->rank = -1;
	stk_a->next = stk_a;
	stk_a->prev = stk_a;
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		*p;
	const int	*s;
	size_t		i;

	p = (int *)dest;
	s = (const int *)src;
	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	return (dest);
}

static void ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void quick_sort(int *arr, int left, int right)
{
	int pivot;
	int i;
	int j;

	if (left >= right)
		return ;
	pivot = arr[left];
	i = left;
	j = right;
	while (1)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i >= j)
			break;
		ft_swap(&arr[i], &arr[j]);
		i++;
		j--;
	}
	quick_sort(arr, left, j);
	quick_sort(arr, j + 1, right);
}

static void compression(int *rank_arr, int *arr, int *sorted_arr, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (arr[i] != sorted_arr[j])
			j++;
		rank_arr[i] = (j + 1);
		i++;
	}
}

int *make_rank_arr(int *arr, int size)
{
	int *rank;
	int *sorted_arr;

	rank = (int *)malloc(sizeof(int) * size);
	if (!rank)
		return (NULL);
	sorted_arr = (int *)malloc(sizeof(int) * size);
	if (!sorted_arr)
		return (NULL);
	ft_memcpy(sorted_arr, arr, size);
	quick_sort(sorted_arr, 0, size - 1);
	compression(rank, arr, sorted_arr, size);
	free(sorted_arr);
	return (rank);
}

t_stack *push_back(t_stack *stk_a, int rank)
{
	t_stack *new;
	t_stack *tail;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->rank = rank;
	tail = stk_a->prev;
	tail->next = new;
	new->prev = tail;
	new->next = stk_a;
	stk_a->prev = new;
	return (new);
}

void free_stack(t_stack *stk_a)
{
	t_stack *cur;
	t_stack *tmp;

	cur = stk_a->next;
	while (cur != stk_a)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	free(stk_a);
}

t_stack *stack_a_utils(int *arr, int size)
{
	t_stack *stk_a;
	int *rank_arr;
	int i;

	stk_a = (t_stack *)malloc(sizeof(t_stack));
	if (!stk_a)
		return (NULL);
	stack_a_init(stk_a);
	rank_arr = make_rank_arr(arr, size);
	i = 0;
	while (i < size)
	{
		if (!push_back(stk_a, rank_arr[i]))
		{
			free_stack(stk_a);
			return (NULL);
		}
		i++;
	}
	return (stk_a);
}

// #include <stdio.h>
// int main(void)
// {
// 	int a[] = {5, 4 ,3 ,2 ,1 };
// 	t_stack *a_stack = stack_a_utils(a, 5);
// 	t_stack *b_stack = (t_stack *)malloc(sizeof(t_stack));
// 	b_stack->rank = -1;
// 	b_stack->next = b_stack;
// 	b_stack->prev = b_stack;
	
// 	push(b_stack, a_stack);
// 	push(b_stack, a_stack);

// 	t_stack *cur = b_stack->next;
// 	while (cur != b_stack)
// 	{
// 		printf("%d ", cur->rank);
// 		cur = cur->next;
// 	}
// }