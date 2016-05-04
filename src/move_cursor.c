#include "shell.h"

int		calc_line(t_env *e, char *str)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 0;
	while (i < e->curs_pos && str[i] != '\n')
		i++;
	ret += (i + e->prompt_len) / e->width;
	while (i < e->curs_pos)
	{
		j = 0;
		if (str[i] == '\n')
		{
			i++;
			ret++;
		}
		while (str[i] != '\n' && i < e->curs_pos)
		{
			i++;
			j++;
		}
		ret += j / e->width;
	//	ft_printf("j = %d -- ret = %d\n", j, ret);
	}
	return (ret);
}

void move_cursor_line(t_env *e, int input, char *str)
{
	int		diff;
	int		move;

	diff = e->curs_max;
	move = 0;
	if (input == HOME && e->curs_pos)
	{
		tputs(tgoto(tgetstr("LE", NULL), 0, e->width), 0, ft_putchar2);
		if ((move = calc_line(e, str)))
			tputs(tgoto(tgetstr("UP", NULL), 0, move), 0, ft_putchar2);
		tputs(tgoto(tgetstr("RI", NULL), 0, e->prompt_len), 0, ft_putchar2);
		e->curs_pos = 0;
	}
	else if (input == END && e->curs_max - e->curs_pos > 0)
	{
		tputs(tgetstr("rc", NULL), 0, ft_putchar2);
		tputs(tgetstr("sc", NULL), 0, ft_putchar2);
		e->curs_pos = e->curs_max;
	}
}

void move_cursor_word(t_env *e, int input)
{
	e = (void*)e;
	if (input == LEFT_OPT)
	{

	}
	else if (input == RIGHT_OPT)
	{

	}
}
