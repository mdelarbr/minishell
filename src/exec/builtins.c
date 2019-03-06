/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 15:11:40 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:58:25 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

int			exec_echo(char **res)
{
	int		i;

	if (!res[1])
		ft_put("\n", 0, RESET);
	else
	{
		if ((ft_strcmp(res[1], "-n")) == 0)
		{
			i = 1;
			while (res[++i])
				ft_put(res[i], 0, RESET);
		}
		else
		{
			i = 1;
			while (res[i + 1])
			{
				ft_put(res[i], 0, RESET);
				ft_put(" ", 0, RESET);
				i++;
			}
			ft_put(res[i], 1, RESET);
		}
	}
	return (1);
}

int			exec_oldcd(t_var *l_var, t_var *save)
{
	char	*buf;
	char	*tmp;

	buf = NULL;
	while (l_var && (ft_strcmp(l_var->name, "OLDPWD") != 0))
		l_var = l_var->next;
	if (!l_var)
	{
		ft_put("OLDPWD not set.", 1, RESET);
		l_var = save;
		return (-1);
	}
	tmp = ft_strdup(l_var->data);
	free(l_var->data);
	l_var->data = getcwd(buf, 0);
	chdir(tmp);
	ft_put(tmp, 1, RESET);
	l_var = save;
	find_or_create(l_var, "PWD");
	free(tmp);
	free(buf);
	return (1);
}

int			exec_solocd(t_var *l_var, t_var *save)
{
	char	*buf;

	buf = NULL;
	find_or_create(l_var, "OLDPWD");
	l_var = save;
	while (l_var && (ft_strcmp(l_var->name, "HOME") != 0))
		l_var = l_var->next;
	if (!l_var)
	{
		ft_put("HOME not set.", 1, RESET);
		l_var = save;
		return (-1);
	}
	chdir(l_var->data);
	l_var = save;
	find_or_create(l_var, "PWD");
	l_var = save;
	return (1);
}

int			exec_cd(char **res, t_var *l_var)
{
	t_var	*save;
	char	*buf;

	save = l_var;
	buf = NULL;
	if (!(res[1]))
	{
		if (exec_solocd(l_var, save) == 1)
			return (1);
		return (-1);
	}
	if (ft_strcmp(res[1], "-") == 0)
	{
		if (exec_oldcd(l_var, save) == 1)
			return (1);
		return (-1);
	}
	simple_cd(res, l_var);
	l_var = save;
	return (1);
}

int			find_builtins(char **res, t_var **l_var)
{
	int		done;

	done = 0;
	if (ft_strcmp(res[0], "echo") == 0)
		done += exec_echo(res);
	else if (ft_strcmp(res[0], "cd") == 0)
		done += exec_cd(res, (*l_var));
	else if (ft_strcmp(res[0], "setenv") == 0)
		done += exec_setenv(res, (*l_var));
	else if (ft_strcmp(res[0], "unsetenv") == 0)
		done += exec_unsetenv(res, l_var);
	else if (ft_strcmp(res[0], "env") == 0)
		done += exec_env((*l_var));
	else if (ft_strcmp(res[0], "exit") == 0)
		done = -3;
	else
		return (done);
	return (done);
}
