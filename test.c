#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef	struct	s_pos
{
	int	a;
	int	b;
	int	count_a;
	int	count_b;
}	t_pos;


void	ft_swap(int *element1, int *element2)
{
	int	temp;

	temp = *element1;
	*element1 = *element2;
	*element2 = temp;
}

void push_b(int *s_a, int *s_b, t_pos *data)
{
	int i;
	int tmp;

	i = 0;
	tmp = s_a[0];
	while (i < data->count_a -1)
	{
		ft_swap(&s_a[i], &s_a[i + 1]);
		i++;
	}
	if (data->b != 0)
	{
		i = data->b + 1;
		while (i--)
			ft_swap(&s_b[i], &s_b[i + 1]);
		ft_swap(&s_b[0], &tmp);
	}
	else
	    ft_swap(&s_b[0], &tmp);
	s_a[data->count_a - 1] = 0;
	data->b++;
	write(1, "pb\n", 3);
}

void push_a(int *s_a, int *s_b, t_pos *data)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = s_b[0];
	while (i < data->count_b - 1)
	{
		ft_swap(&s_b[i], &s_b[i + 1]);
		i++;
	}
	i = 0;
	while (s_a[i] != 0)
		i++;
	while (i--)
		ft_swap(&s_a[i + 1], &s_a[i]);
	ft_swap(&s_a[0], &tmp);
	data->b--;
	write(1, "pa\n", 3);
}

void	sort_a(int *s)
{
	ft_swap(&s[0], &s[1]);
	write(1, "sa\n", 3);
}

void	sort_b(int *s)
{
	ft_swap(&s[0], &s[1]);
	write(1, "sb\n", 3);
}

void	rotate_a(int *s, int count)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = s[i];
	while (i < count)
	{
		ft_swap(&s[i], &s[i + 1]);
		i++;
	}
	ft_swap(&s[count], &tmp);
		write(1, "ra\n", 3);
}

void	rotate_reverse_a(int *s, int count)
{
	int	i;
	int	tmp;

	i = count - 1;
	tmp = s[count - 1];
	while (i >= 0)
	{
		ft_swap(&s[i], &s[i - 1]);
		i--;
	}
	ft_swap(&s[0], &tmp);
	write(1, "rra\n", 4);
}

int	pos_checking(int *s_a, int count, int pos)
{
	int	i;

	i = 0;
	while (s_a[i] != s_a[pos])
	{
		if (s_a[i] > s_a[pos])
			return (i);
		i++;
	}
	while (i <= count)
	{
		if (s_a[i] < s_a[pos])
			return (i);
		i++;
	}
	return (0);
}

int	sort_checking(int *num_col, int max)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < max - 1)
	{
		if (num_col[i] > num_col[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	abs(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

void	stack_a_sort(int *sa, int *sb, t_pos *data)
{
	while (pos_checking(sa, data->count_a - 1, data->a) != 0)
	{
		printf("%d :[%d]\n", data->a,pos_checking(sa, data->count_a - 1, data->a));
		for (int m = 0; m < 5; m++)
			printf("%d, ", sa[m]);
			puts("");
		printf("a_pos:%d\n", data->a);
		if (pos_checking(sa, data->count_a - 1, data->a) >= data->count_a / 2)
		{
			rotate_reverse_a(sa, data->count_a);
			if (data->a == data->count_a - 1)
				data->a = 0;
			else
				data->a++;
		}
		else
		{
			rotate_a(sa, data->count_a - 1);
			if (data->a == 0)
				data->a = data->count_a - 1;
			else
				data->a--;
		}
		if (sa[0] > sa[1])
		{
			sort_a(sa);
			data->a++;
		}
		printf("%d data->a\n", pos_checking(sa, data->count_a - 1, data->a));
	}
}

void	push_while(int *sa, int *sb, t_pos *data)
{
	int	i;

	i = 0;
	while (i++ <= data->a)
		push_b(sa, sb, data);
	data->a = i - 2 - data->a;
	while (i < data->count_a - 1)
	{
		if (sb[0] > sa[data->count_a - 1 - data->b])
			break ;
		if (sa[0] > sb[0] && sa[1] != 0)
		{
			rotate_a(sa, data->count_a - 1 - data->b); 
			break ;
		}
		i++;
	}
	if (sa[0] < sb[0] && sa[1] != 0)
		rotate_a(sa, data->count_a - 1 - data->b);
	i = 0;
	while (data->b != 0 && i < data->count_a - 1) 
	{
		if (sa[data->count_a - 1 - data->b] != 0 && sa[1] != 0)
			rotate_reverse_a(sa, data->count_a - 1 - data->b);
		if (sa[0] > sa[1] && sa[1] != 0)
			sort_a(sa);
		if (abs(sa[1] - sa[0]) -  abs(sa[0] - sb[0]) == 0 || \
		abs(sa[0] - sa[data->count_a - 1 - data->b]) > abs(sa[0] - sb[0])) 
			push_a(sa, sb, data);
		else if (sa[data->count_a - 1 - data->b] != 0 && sa[1] != 0)
			rotate_reverse_a(sa, data->count_a - 1 - data->b);
		i++;
	}
	if (i == data->count_a - 1)
	{
		while (data->b != 0)
			push_a(sa, sb, data);
		data->a = 0;
	}
	data->a = 0;
	stack_a_sort(sa,sb, data);
	for (int m = 0; m < 5; m++)
		printf("%d, ", sa[m]);
	puts("");
}

int	search_a(int *sa, t_pos *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->count_a)
	{
		j = i + 1;
		while (j < data->count_b)
		{
			if (sa[i] > sa[j])
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

void	quick(int *sa, int *sb, t_pos *data)
{
	data->a += search_a(sa, data);
	if (data->a == 0 && sa[0] > sa[1])
	{
		sort_a(sa);
		data->a++;
	}
	push_while(sa, sb, data);
	printf("[%d]\n", search_a(sa, data));
	data->a += search_a(sa, data);
	for (int m = 0; m < 5; m++)
		printf("%d, ", sa[m]);
		puts("");
	if (!sort_checking(sa, data->count_a) || data->a == data->count_a)
		quick(sa, sb, data);
}

void	set_default(t_pos *data, int count)
{
	data->count_a = count;
	data->count_b = count;
	data->a = 0;
	data->b = 0;
}

int main(void)
{
	int stack_a[5] = {3,4,2,1,5};
	// int stack_a[4] = {4,1,3,2};
	// int stack_a[5] = {2,3,1,4,5};
	//int stack_a[5] = {2,4,3,5,1};
	//int stack_a[5] = {5,4,3,2,1};
	//int stack_a[5] = {1,2,3,5,4};
	int	stack_b[5] = {0,0,0,0,0};
	int count = 5;
	t_pos	data;

	set_default(&data, count);
	data.a += search_a(stack_a, &data);
	if (data.a == 0 && stack_a[0] > stack_a[1])
	{
		sort_a(stack_a);
		data.a++;
	}
//	stack_a_sort(stack_a, stack_b, &data);
	quick(stack_a, stack_b, &data);
	return (0);
}
