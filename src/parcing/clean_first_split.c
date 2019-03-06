/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clean_first_split.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 11:49:09 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 10:33:01 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

char		**first_splitbis(char **res, int *tab, char *s)
{
	res[tab[1]] = malloc(sizeof(char) * (next_first(s, tab[0]) + 1));
	while (s[tab[0]] && (s[tab[0]] != ';' || (s[tab[0]] == ';' && (tab[0] == 0
	|| s[tab[0] - 1] == '\\'))))
	{
		res[tab[1]][tab[2]] = s[tab[0]];
		tab[2]++;
		tab[0]++;
	}
	if (s[tab[0]] && (s[tab[0]] == ';' && (s[0] == 0 || s[tab[0] - 1] != '\\')))
	{
		res[tab[1]][tab[2]] = '\0';
		tab[2] = 0;
		tab[1]++;
		tab[0]++;
	}
	else if (!s[tab[0]])
	{
		res[tab[1]][tab[2]] = '\0';
		tab[1]++;
	}
	return (res);
}

char		**first_split(char *buf)
{
	int		tab[3];
	char	**res;

	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	res = malloc(sizeof(char*) * (count_first(buf) + 1));
	if (nul_split(buf) == 1)
	{
		free(res);
		return (NULL);
	}
	while (buf[tab[0]])
		res = first_splitbis(res, tab, buf);
	res[tab[1]] = NULL;
	return (res);
}
