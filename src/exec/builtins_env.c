/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_env.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 16:25:36 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:58:35 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void		free_unset(t_var *l_var)
{
	free(l_var->data);
	free(l_var->name);
	free(l_var);
}

int			exec_unsetenv_bis(char **res, t_var *start, t_var *ndel)
{
	if ((ft_strcmp(res[1], start->next->name) == 0))
	{
		if (!(start->next->next))
			ndel = NULL;
		else
			ndel = start->next->next;
		free_unset(start->next);
		start->next = ndel;
		return (1);
	}
	start = start->next;
	return (0);
}

int			exec_unsetenv(char **res, t_var **l_var)
{
	t_var	*start;
	t_var	*ndel;

	if (!res[1] || res[2])
	{
		ft_put("unsetenv: usage: [NAME]", 1, RED);
		return (-2);
	}
	start = (*l_var);
	if (ft_strcmp((*l_var)->name, res[1]) == 0)
	{
		start = (*l_var)->next;
		free_unset((*l_var));
		(*l_var) = start;
		return (1);
	}
	while (start->next)
	{
		if (exec_unsetenv_bis(res, start, ndel) == 1)
			break ;
		start = start->next;
	}
	return (1);
}

int			exec_env(t_var *l_var)
{
	t_var	*start;

	start = l_var;
	while (l_var)
	{
		ft_put(l_var->name, 0, RESET);
		ft_put("=", 0, RESET);
		ft_put(l_var->data, 1, RESET);
		l_var = l_var->next;
	}
	l_var = start;
	return (1);
}

int			exec_setenv(char **res, t_var *l_var)
{
	t_var	*save;

	save = l_var;
	if (!res[1] || !res[2] || res[3])
	{
		ft_put("setenv: usage: [NAME], [DATA]", 1, RESET);
		return (-2);
	}
	while (save->next && ft_strcmp(save->name, res[1]) != 0)
		save = save->next;
	if (ft_strcmp(save->name, res[1]) != 0)
	{
		save->next = malloc(sizeof(t_var));
		save = save->next;
		save->name = ft_strdup(res[1]);
		save->data = ft_strdup(res[2]);
		save->next = NULL;
	}
	else
	{
		free(save->data);
		save->data = ft_strdup(res[2]);
	}
	return (1);
}
