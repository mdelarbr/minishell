/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lnk_list.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 13:06:14 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 12:12:29 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void		restart_prog(int i)
{
	if (i == SIGINT)
		ft_putchar('\n');
}

void		data_lnklist(char *env, t_var *l_var)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (env[i] != '=')
		i++;
	l_var->data = (char*)malloc(sizeof(char) * ((ft_strlen(env) - i) + 1));
	while (env[++i])
	{
		l_var->data[j] = env[i];
		j++;
	}
	l_var->data[j] = '\0';
}

void		name_lnklist(char *env, t_var *l_var)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	l_var->name = (char*)malloc(sizeof(char) * i + 1);
	l_var->name[i--] = '\0';
	while (i >= 0)
	{
		l_var->name[i] = env[i];
		i--;
	}
}

t_var		*fill_lnklist(char **env)
{
	int		i;
	t_var	*l_var;
	t_var	*start;

	i = 0;
	l_var = malloc(sizeof(t_var));
	start = l_var;
	while (env[i])
	{
		name_lnklist(env[i], l_var);
		data_lnklist(env[i], l_var);
		l_var->next = malloc(sizeof(t_var));
		l_var = l_var->next;
		i++;
	}
	name_lnklist("PROMPT=", l_var);
	data_lnklist("=minishell", l_var);
	l_var->next = NULL;
	l_var = start;
	return (l_var);
}

void		free_lnklist(t_var *l_var)
{
	t_var	*tmp;

	while (l_var)
	{
		tmp = l_var;
		free(l_var->name);
		free(l_var->data);
		l_var = l_var->next;
		free(tmp);
	}
	free(l_var);
}
