/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_nothing.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 18:38:49 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 14:11:19 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void		second_if_forest(int *start, char *s)
{
	if (s[*start] == '\\' && s[*start + 1] == '$')
		(*start)++;
	if (s[*start] == '\\' && s[*start + 1] == '\\')
		(*start)++;
	if (s[*start] == '\\' && s[*start + 1] == '"')
		(*start)++;
	if (s[*start] == '\\' && s[*start + 1] == ';')
		(*start)++;
}

char		*fill_nothing_solve(char *s, int *tab, t_var *l_var, char *res)
{
	char	*var;
	int		ivar;

	ivar = 0;
	if (s[tab[0]] == '$' && (tab[0] == 0 || s[tab[0] - 1] != '\\'))
	{
		var = fill_var(s, &tab[0], l_var);
		if (ft_strcmp(var, "") == 0)
		{
			res[tab[1]] = '\0';
			ft_strdel(&var);
			return (res);
		}
		while_double(var, ivar, res, tab);
		ft_strdel(&var);
	}
	else
	{
		res[tab[0]] = s[tab[1]];
		(tab[0])++;
		(tab[1])++;
	}
	return (res);
}

char		*fill_nothing(char *s, int *i, t_var *l_var)
{
	char	*res;
	char	*tmp;
	int		tab[2];

	tab[0] = 0;
	tab[1] = (*i);
	while (((s[*i] < 9 || s[*i] > 13) && s[*i] != ' ') && s[*i])
		(*i)++;
	res = malloc(sizeof(char) * ((*i - tab[1]) + 1));
	while (s[tab[1]] && ((s[tab[1]] < 9 || s[tab[1]] > 13) && s[tab[1]] != ' '))
	{
		second_if_forest(&tab[1], s);
		tmp = fill_nothing_solve(s, tab, l_var, res);
		if (tmp)
			res = ft_strfjoin(res, tmp);
	}
	res[tab[0]] = '\0';
	return (res);
}

char		*fill_var(char *s, int *i, t_var *l_var)
{
	char	*res;
	char	*name;
	int		size;
	t_var	*start;

	start = l_var;
	size = (*i) + 1;
	while (s[size + 1] && ((s[size + 1] < 9 || s[size + 1] > 13) &&
		s[size + 1] != ' ') && s[size + 1] != '"')
		size++;
	name = ft_strsub(s, (*i) + 1, (size - (*i)));
	while (start->next)
	{
		if ((ft_strcmp(start->name, name)) == 0)
		{
			res = ft_strdup(start->data);
			(*i) = size + 1;
			free(name);
			return (res);
		}
		start = start->next;
	}
	free(name);
	(*i) = size + 1;
	return (ft_strdup(""));
}
