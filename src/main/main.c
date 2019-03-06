/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 19:30:42 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:03:05 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void	restart(int i)
{
	if (i == SIGINT)
	{
		ft_putchar('\n');
		ft_put("minishell >>", 0, BLUE);
	}
}

void	ft_put_prompt(t_var *l_var, char *color)
{
	t_var	*save;

	save = l_var;
	ft_putstr(color);
	while (save && ft_strcmp("PROMPT", save->name) != 0)
		save = save->next;
	if (!save)
		ft_putstr("prompt not found");
	else
		ft_putstr(save->data);
	ft_putstr(">>");
	ft_putstr(RESET);
}

void	ft_put(char *str, int space, char *color)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr(RESET);
	if (space)
		write(1, "\n", 1);
}

int		main_use(t_var **l_var, char *buf)
{
	ssize_t		i;
	int			ret;

	while (1)
	{
		ft_put_prompt((*l_var), BLUE);
		signal(SIGINT, restart);
		g_pid = 0;
		while ((i = read(0, buf, 8192)) > 0)
		{
			buf[i - 1] = '\0';
			if (i == 8192)
				ft_put("Error: to many characters", 0, RED);
			else
			{
				if ((ret = make_clean(buf, l_var)) == -1)
					break ;
				if (ret == -3)
					return (-1);
			}
			ft_put_prompt((*l_var), BLUE);
		}
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char		buf[8192];
	int			ret;
	t_var		*l_var;

	l_var = fill_lnklist(env);
	(void)ac;
	(void)av;
	main_use(&l_var, buf);
	free_lnklist(l_var);
	return (0);
}
