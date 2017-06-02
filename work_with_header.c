//
// Created by Oleksiy Kres on 15/29/17.
//

#include "op.h"

int 	check_if_comand_is(char *command, int *cur_com_size, unsigned int *prog_s )
{
    int i;
    int size[] = {4, 4, 0, 0, 0, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};
    int codage_octal[] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};
    char *comm[] = {"live", "ld", "st", "add", "sub", "and", "or",
                    "xor", "zjmp", "ldi", "sti", "fork", "lld",
                    "lldi", "lfork", "aff"};

    i = 0;
    *prog_s += 2;
    while (i < 16)
    {
        if (ft_strcmp(command, comm[i]) == 0)
        {
            if (cur_com_size)
                *cur_com_size = size[i];
            if (prog_s)
                *prog_s += codage_octal[i] - 1;
            return (i + 1);
        }
        i++;
    }
    return (MAX_INT);
}

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

unsigned int	do_big_endian(unsigned int magic, int size)
{
	unsigned int	res;
	int 			i;

	i = 0;
	res = 0;
	size = (size - 1) * 8;
	while (i <= size)
	{
		res |= ((magic >> (size - i) & 0xFF)) << i;
		i += 8;
	}
	return (res);
}

void			fill_name_and_comment(t_asm *head)
{
	int i;

	i = 0;
	while (head->comm[i])
	{
		head->header->comment[i] = head->comm[i];
		i++;
	}
	i = 0;
	while (head->name[i])
	{
		head->header->prog_name[i] = head->name[i];
		i++;
	}
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


void			get_prog_size(t_asm *head)
{
	t_asm			*begin;
	unsigned int 	res;
    int             cur_com_size;

	res = 0;
	begin = head;
    cur_com_size = 4;
	while (begin)
	{
        if (*(begin->lable) != '\0')
            begin->program_s = head->header->prog_size;
        check_if_comand_is(begin->command, &cur_com_size, &(begin->header->prog_size));
		begin->header->prog_size += begin->what_args[0] + begin->what_args[1] + begin->what_args[2];
		if (if_lable(head->l_flag))
		{
			res += find_lable(head, begin->args[get_index(begin->l_flag)]);
		}
		begin = begin->next;
	}
	head->header->prog_size = do_big_endian(res, 4);
}

void			header_parse(t_asm *head, int fd)
{
	t_asm *begin;

	begin = head;
	head->header->magic = do_big_endian(COREWAR_EXEC_MAGIC, 4);
	ft_bzero(head->header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(head->header->comment, COMMENT_LENGTH + 1);
	fill_name_and_comment(head);
	get_prog_size(head);

}
