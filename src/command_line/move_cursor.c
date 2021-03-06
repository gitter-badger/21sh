#include "shell.h"

void		move_cursor_line(t_env *e, int input, char *str)
{
	int		diff;
	int		move;

	diff = e->curs_max;
	move = 0;
	if (input == HOME && e->curs_pos)
	{
		tputs(tgoto(tgetstr("LE", NULL), 0, e->width), 0, ft_putchar2);
		if ((move = calc_line(e, str, e->curs_pos)))
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

static void	move_cursor_word_right(t_env *e, char *str)
{
	int		j;
	int		blank;

	j = 0;
	blank = ft_iswhitespace(str[e->curs_pos]);
	while (e->curs_pos <= e->curs_max)
	{
		if (ft_iswhitespace(str[e->curs_pos]) != blank ||
				e->curs_pos == e->curs_max)
		{
			go_to_position(e, str, e->curs_pos);
			break ;
		}
		e->curs_pos++;
		j++;
	}
}

static void	move_cursor_word_left(t_env *e, char *str)
{
	int		j;
	int		blank;

	j = 0;
	blank = ft_iswhitespace(str[e->curs_pos]);
	while (e->curs_pos >= 0)
	{
		if (ft_iswhitespace(str[e->curs_pos]) != blank || e->curs_pos == 0)
		{
			e->curs_pos++;
			go_to_position(e, str, e->curs_pos);
			break ;
		}
		e->curs_pos--;
		j++;
	}
}

void		move_cursor_word(t_env *e, int input, char *str)
{
	if (input == LEFT_OPT)
		move_cursor_word_left(e, str);
	else if (input == RIGHT_OPT)
		move_cursor_word_right(e, str);
}
