//
// Created by Oleksiy Kres on 6/2/17.
//
#include "op.h"

int	size[] = {4, 4, 0, 0, 0, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};
int codage_octal[] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};

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

void	write_codage_octal(t_asm *head, int fd)
{

}


void	parse_arguments(t_asm *head)
{
	int i;

	i = 0;
	while (i < head->amount_of_args)
	{
		//	if (if_lable(head->l_flag))
		//get_facking_lable(head);
	}
}

void	write_op_code(t_asm *head, int op_c, int fd)
{

	int i;
	static int val_cur;
	int val_next;

	val_next = 1;
	head->cur_size = size[op_c - 1];
	head->cur_codage_octal = codage_octal[op_c - 1];
	write(fd, &op_c, 1);
	if (head->cur_codage_octal)
	{
		val_next++;
		write_codage_octal(head, fd);
	}
	parse_arguments(head);
}
