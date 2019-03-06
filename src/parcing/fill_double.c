/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_double.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 16:51:08 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 14:24:24 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void		if_forest(int *tab, char *s)
{
	if (s[tab[0]] && s[tab[0]] == '\\' && s[tab[0] + 1] == '\\')
		(tab[0])++;
	if (s[tab[0]] && s[tab[0]] == '\\' && s[tab[0] + 1] == '$')
		(tab[0])++;
	if (s[tab[0]] && s[tab[0]] == '\\' && s[tab[0] + 1] == '"')
		(tab[0])++;
}

void		while_double(char *var, int ivar, char *res, int *tab)
{
	while (var[ivar])
	{
		res[tab[1]] = var[ivar];
		(tab[1])++;
		ivar++;
	}
}

char		*fill_double_solve(char *s, int *tab, t_var *l_var, char *res)
{
	char	*var;
	int		ivar;

	var = NULL;
	ivar = 0;
	if_forest(tab, s);
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
	}
	else
	{
		res[tab[1]] = s[tab[0]];
		(tab[0])++;
		(tab[1])++;
	}
	ft_strdel(&var);
	return (res);
}

char		*fill_double(char *s, int *i, t_var *l_var)
{
	char	*res;
	int		tab[2];
	char	*tmp;

	tab[0] = ++(*i);
	tab[1] = 0;
	while (s[*i] && (s[*i] != '"' || s[*i - 1] == '\\'))
		(*i)++;
	if (!s[*i])
	{
		ft_put("error :end the \", its not 21sh bro.", 1, RESET);
		return (NULL);
	}
	if (!(res = malloc(sizeof(char) * ((*i - tab[0]) + 1))))
		return (NULL);
	while (tab[0] < *i)
	{
		if_forest(tab, s);
		tmp = fill_double_solve(s, tab, l_var, res);
		if (tmp)
			res = ft_strfjoin(res, tmp);
	}
	res[tab[1]] = '\0';
	*i = tab[0];
	return (res);
}
