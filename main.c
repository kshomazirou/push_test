#include "push_swap.h"
#include <stdio.h>

static int	judge(int s, long int n, int now)
{
	if (s == 1 && ((LONG_MAX / 10 < n) || (LONG_MAX - n * 10 - now <= 0)))
		return (1);
	if (s == -1 && ((LONG_MIN / 10 > n) || (LONG_MIN + n * 10 + now >= 0)))
		return (-1);
	return (0);
}

int	ft_atoi(const char *str, int *error)
{
	long int	result;
	int			num;
	int			sign;

	result = 0;
	num = 0;
	sign = 1;
	while ((str[num] >= '\t' && str[num] <= '\r') || str[num] == ' ')
		num++;
	if (str[num] == '-' || str[num] == '+')
	{
		if (str[num] == '-')
			sign = -1;
		num++;
	}
	if (str[num] < '0' || str[num] > '9')
	{
		*error = 1;
		return (0);
	}
	while (str[num] >= '0' && str[num] <= '9')
	{
		if (judge(sign, result, str[num] - '0') == 1)
			return ((int)LONG_MAX);
		if (judge(sign, result, str[num] - '0') == -1)
			return ((int)LONG_MIN);
		result = result * 10 + (str[num] - '0');
		num++;
	}
	return ((int)result * sign);
}

//英文字が含まれていないかの確認
int	judge_only_number(char *c)
{
	int	i;
	int	max;
	int	count;

	i = 0;
	max = 0;
	count = 0;
	while (c[max])
		max++;
	while (c[i])
	{
		if ((c[i] >= '\t' && c[i] <= '\r') || c[i] == ' ')
			count++;
		if ((c[i] >= '0' && c[i] <= '9') || (c[i] == '+' || c[i] == '-'))
			count++;
		i++;
	}
	if (max == count)
		return (0);
	else
		return (1);
}

//数値化＋文字なし確認
int	atoi_jon(char *argv)
{
	long	num;
	int		error;

	num = 0;
	error = 0;
	num = ft_atoi(argv, &error);
	if (judge_only_number(argv))
		return (1);
	if (num > INT_MAX || num < INT_MIN || error == 1)
		return (2);
	return (0);
}

//数の重複がないかの確認
int	num_duplicate(int *num_col, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count)
		{
			if (i != j && num_col[i] == num_col[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
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

void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t			num;
	unsigned char	*text;
	unsigned char	val;

	num = 0;
	text = (unsigned char *)buf;
	val = (unsigned char )ch;
	while (num < n)
	{
		text[num] = val;
		num++;
	}
	return (buf);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*box;

	if (!n || !size)
	{
		n = 1;
		size = 1;
	}
	if (SIZE_MAX / n < size)
		return (malloc(SIZE_MAX));
	box = (void *)malloc(n * size);
	if (box == NULL)
		return (NULL);
	ft_bzero(box, n * size);
	return (box);
}

void	ft_swap(int *element1, int *element2)
{
	int	temp;

	temp = *element1;
	*element1 = *element2;
	*element2 = temp;
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
	while (i--)// here is strange
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
int *cc(int *s_a, int count)
{
	int	*new_s;
	int	i;
	int	j;
	int	judge;

	i = 0;
	new_s = ft_calloc(count, sizeof(int));
	if (!new_s)
		return (free(s_a), NULL);
	while (i < count)
	{
		j = 0;
		judge = s_a[i];
		while (j < count)
		{
			if (s_a[i] < s_a[j])
				new_s[j] += 1;
			j++;
		}
		i++;
	}
	free(s_a);
	return (new_s);
}

void	set_default(t_pos *data, int count)
{
	data->count_a = count;
	data->count_b = count;
	data->a = 0;
	data->b = 0;
}

void	stack_free(int *sa, int *sb)
{
	free(sa);
	free(sb);
}

void	stack_a_sort(int *sa, int *sb, t_pos *data)
{
	while (pos_checking(sa, data->count_a - 1, data->a) != 0)
	{
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
	}
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
		if (abs(sa[1] - sa[0]) - abs(sa[0] - sb[0]) == 0 || \
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
	stack_a_sort(sa, sb, data);
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
	data->a += search_a(sa, data);
	if (!sort_checking(sa, data->count_a) || data->a == data->count_a)
		quick(sa, sb, data);
}

void	quick_sorting(int *stack_a, int count)
{
	int		*new_a;
	int		*stack_b;
	t_pos	data;

	set_default(&data, count);
	stack_b = (int *)malloc((count) * sizeof(int));
	if (stack_b == NULL)
	{
		free(stack_a);
		write(1, "Error\n", 6);
		return ;
	}
	new_a = cc(stack_a, data.count_a);
	free(stack_a);
	if (sort_checking(new_a, data.count_a))
	{
		stack_free(new_a, stack_b);
		return ;
	}
	if (count <= 4)
	{
		stack_a_sort(new_a, stack_b, &data);
		return ;
	}
	quick(stack_a, stack_b, &data);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	error;
	int	*num_col;

	error = 0;
	i = 1;
	while (i < argc)
		if (atoi_jon(argv[i++]))
			return (write(1, "Error\n", 6), 2);
	num_col = (int *)malloc((argc - 1) * sizeof(int));
	if (num_col == NULL)
		return (write(1, "Error\n", 6), 2);
	i = 0;
	while (i < argc - 1)
	{
		num_col[i] = ft_atoi(argv[i + 1], &error);
		if (error)
			return (free(num_col), 2);
		i++;
	}
	if (num_duplicate(num_col, argc - 1) == 0)
		quick_sorting(num_col, argc - 1);
	else
		write(1, "Error\n", 6);
	free(num_col);
	return (0);
}
