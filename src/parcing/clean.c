/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clean.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/24 17:40:01 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 14:22:12 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_filling_while(char *s, int *tab, t_var *l_var)
{
	char	*tmp;
	char	*res;

	res = ft_strdup("");
	tmp = NULL;
	while (s[tab[0]] && ((s[tab[0]] >= 9 && s[tab[0]] <= 13) ||
				s[tab[0]] == ' '))
		(tab[0])++;
	if (s[tab[0]] == '"' && (tab[0] == 0 || s[tab[0] - 1] != '\\'))
	{
		tmp = fill_double(s, &tab[0], l_var);
		res = ft_strfjoin(res, tmp);
		(tab[0])++;
	}
	else if (s[tab[0]] == '\'' && (tab[0] == 0 || s[tab[0] - 1] != '\\'))
	{
		res = filling_simple(s, tab, tmp, res);
		(tab[0])++;
	}
	else
		res = filling_wbis(s, tab, l_var, res);
	if (tmp)
		ft_strdel(&tmp);
	return (res);
}

int			ft_filling(char **split, char *s, t_var *l_var)
{
	int		tab[2];
	char	*res;

	tab[0] = 0;
	tab[1] = 0;
	while (s[tab[0]])
	{
		if ((res = ft_filling_while(s, tab, l_var)) == NULL)
		{
			ft_strdel(&res);
			return (-1);
		}
		if (ft_strcmp(res, "") != 0)
		{
			split[tab[1]] = ft_strdup(res);
			tab[1]++;
		}
		ft_strdel(&res);
	}
	split[tab[1]] = NULL;
	return (1);
}

char		**strsplit(char *s, t_var *l_var)
{
	char	**split;
	int		words;
	int		i;

	i = 0;
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
		i++;
	if (!s[i])
		return (NULL);
	words = count_word(s);
	if (!(split = (char**)malloc(sizeof(char*) * (words + 1))))
		return (0);
	if (ft_filling(split, s, l_var) == -1)
		return (NULL);
	return (split);
}

int			make_clean(char *buf, t_var **l_var)
{
	char	**fres;
	int		ret;
	int		i;
	char	**res;

	i = -1;
	fres = first_split(buf);
	if (fres == NULL)
		return (-1);
	while (fres[++i])
	{
		if ((res = strsplit(fres[i], (*l_var))) == NULL)
			break ;
		if ((ret = find_builtins(res, l_var)) == 0)
			main_exec(res, (*l_var));
		if (ret == -3)
		{
			free_tab(fres);
			free_tab(res);
			return (-3);
		}
		free_tab(res);
	}
	free_tab(fres);
	return (ret);
}
