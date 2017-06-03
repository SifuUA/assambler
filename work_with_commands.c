//
// Created by Oleksiy Kres on 6/2/17.
//
#include "op.h"

int 			if_lable(int *ar)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (ar[i] > 0)
			return (1);
		i++;
	}
	return (0);
}

int 			get_index(int *ar)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (ar[i] == 1)
			j = i;
		i++;
	}
	return (j);
}

int 			find_lable(t_asm *begin, char *lable)
{
	t_asm	*node;
	int		res;

	node = begin;
	res = 0;
	while (node)
	{
		if (node->lable && ft_strcmp(node->lable, lable) == 0)
		{
			res = node->what_args[0] + node->what_args[1] + node->what_args[2];
			break ;
		}
		node = node->next;
	}
	/*if (node && (node->l_flag[0] == 1 || node->l_flag[1] == 1 ||
		node->l_flag[2] == 1))
		res += find_lable(begin, begin->args[get_index(begin->l_flag)]);*/ // проблема с записью лейбы, Антон фикс
	return (res);
}

