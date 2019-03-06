/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   use_execve.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 16:36:35 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:58:18 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_path(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	tmp = ft_strfjoin(tmp, s2);
	return (tmp);
}

int		use_execve_acces(char *tmp, char **res, t_var *l_var, char **path)
{
	if ((access(tmp, F_OK)) == 0)
	{
		if ((access(tmp, X_OK)) == -1)
			ft_put("Permission denied.", 1, RESET);
		solve_execve(tmp, res, l_var);
		ft_strdel(&tmp);
		free_tab(path);
		return (0);
	}
	return (1);
}

int		use_execve(char **res, t_var *l_var)
{
	char	**path;
	char	*tmp;
	int		i;
	t_var	*start;

	start = l_var;
	while (start->next && ft_strcmp(start->name, "PATH") != 0)
		start = start->next;
	if (!(start))
		return (-1);
	path = ft_strsplit(start->data, ':');
	i = 0;
	while (path[i])
	{
		tmp = strjoin_path(path[i], res[0]);
		if (use_execve_acces(tmp, res, l_var, path) == 0)
			return (0);
		i++;
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	free_tab(path);
	return (-1);
}

void	error_bis(int i)
{
	if (i == 9)
		ft_put(ERR09, 0, RED);
	else if (i == 10)
		ft_put(ERR10, 0, RED);
	else if (i == 11)
		ft_put(ERR11, 0, RED);
}

void	choose_error(void)
{
	int i;

	srand(time(NULL));
	i = rand();
	i = i % 12;
	if (i == 0)
		ft_put(ERR00, 0, RED);
	else if (i == 1)
		ft_put(ERR01, 0, RED);
	else if (i == 2)
		ft_put(ERR02, 0, RED);
	else if (i == 3)
		ft_put(ERR03, 0, RED);
	else if (i == 4)
		ft_put(ERR04, 0, RED);
	else if (i == 5)
		ft_put(ERR05, 0, RED);
	else if (i == 6)
		ft_put(ERR06, 0, RED);
	else if (i == 7)
		ft_put(ERR07, 0, RED);
	else if (i == 8)
		ft_put(ERR08, 0, RED);
	else
		error_bis(i);
}
