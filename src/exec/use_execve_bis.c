/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   use_execve_bis.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 12:53:59 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 12:58:24 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_env(char *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!(s1 && s2))
		return (0);
	i = 0;
	j = 0;
	if (!(dest = (char*)malloc(sizeof(char) *
					(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 2))))
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = '=';
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**split_env(t_var *l_var)
{
	char	*tmp;
	char	**tab;
	t_var	*save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	save = l_var;
	while (save)
	{
		save = save->next;
		i++;
	}
	save = l_var;
	tab = malloc(sizeof(char*) * (i + 1));
	tab[i] = 0;
	while (i--)
	{
		tmp = ft_strdup(save->name);
		tab[j++] = ft_join_env(tmp, save->data);
		ft_strdel(&tmp);
		save = save->next;
	}
	return (tab);
}

int		solve_execve(char *tmp, char **res, t_var *l_var)
{
	int		i;
	char	**tab;

	g_pid = fork();
	signal(SIGINT, restart_prog);
	tab = split_env(l_var);
	if (g_pid == 0)
	{
		if (execve(tmp, res, tab) == -1)
		{
			free_tab(tab);
			return (-1);
		}
	}
	else
		wait(&i);
	free_tab(tab);
	return (1);
}

int		exec_path(char **res, t_var *l_var)
{
	int		ret;

	ret = 0;
	if (access(res[0], F_OK) == 0)
	{
		ret = 1;
		solve_execve(res[0], res, l_var);
	}
	return (ret);
}

int		main_exec(char **res, t_var *l_var)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (ft_strchr(res[0], '/') != 0)
		i = exec_path(res, l_var);
	else if (l_var != NULL)
		i = use_execve(res, l_var);
	if (i == -1)
		choose_error();
	return (0);
}
