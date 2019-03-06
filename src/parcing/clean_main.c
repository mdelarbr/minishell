/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   clean_main.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 13:07:05 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 14:22:09 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

char	*filling_wbis(char *s, int *tab, t_var *l_var, char *res)
{
	char	*tmp;

	tmp = NULL;
	if (s[tab[0]] == '~' && (tab[0] == 0 || s[tab[0] - 1] != '\\'))
	{
		tmp = fill_home(&tab[0], l_var);
		res = ft_strfjoin(res, tmp);
		ft_strdel(&tmp);
	}
	if (s[tab[0]] == '$' && (tab[0] == 0 || s[tab[0] - 1] != '\\'))
	{
		tmp = fill_var(s, &tab[0], l_var);
		res = ft_strfjoin(res, tmp);
		ft_strdel(&tmp);
	}
	else
	{
		tmp = fill_nothing(s, &tab[0], l_var);
		res = ft_strfjoin(res, tmp);
		ft_strdel(&tmp);
	}
	if (tmp)
		ft_strdel(&tmp);
	return (res);
}
