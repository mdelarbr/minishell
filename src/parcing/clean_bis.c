/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clean_bis.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 11:39:34 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 11:13:35 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

char		*filling_simple(char *s, int *tab, char *tmp, char *res)
{
	if (s[tab[0]] == '\'' && (tab[0] == 0 || s[tab[0] - 1] != '\\'))
	{
		tmp = fill_simple(s, &tab[0]);
		if (!tmp)
			return (NULL);
		res = ft_strfjoin(res, tmp);
		ft_strdel(&tmp);
		tab[0]++;
	}
	return (res);
}

int			count_first(char *s)
{
	int		cnt;
	int		i;

	i = 0;
	cnt = 1;
	while (s[i])
	{
		if (s[i] == ';' && (i == 0 || s[i - 1] != '\\'))
			cnt++;
		if (s[i] == '"' && (i == 0 || s[i - 1] != '\\'))
		{
			i++;
			while (s[i] && ((s[i] != '"' && (i == 0 || s[i - 1] != '\\'))))
				i++;
		}
		if (s[i] && ((s[i] == '\'' && (i == 0 || s[i - 1] != '\\'))))
		{
			i++;
			while (s[i] && ((s[i] != '\'' && (i == 0 || s[i - 1] != '\\'))))
				i++;
		}
		if (s[i])
			i++;
	}
	return (cnt);
}

int			next_first(char *buf, int i)
{
	int		cnt;

	cnt = 0;
	while (buf[i] && ((buf[i] != ';' && (i == 0 || buf[i - 1] != '\\'))))
	{
		i++;
		cnt++;
	}
	return (cnt);
}

int			nul_split(char *buf)
{
	int		i;

	i = 0;
	while (buf[i] && ((buf[i] >= 9 && buf[i] <= 13) || buf[i] == ' ' ||
		buf[i] == ';'))
		i++;
	if (!buf[i])
		return (1);
	return (0);
}

void		free_tab(char **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}
