/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   count_word.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 20:19:38 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 11:13:49 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void	count_word_while(char *s, int *i)
{
	if (s[*i] && (s[*i] == '"' && (i == 0 || s[*i - 1] != '\\')))
	{
		(*i)++;
		while (s[*i] && (s[*i] != '"'))
			(*i)++;
		if (s[*i] && s[*i - 1] == '\\')
		{
			(*i)++;
			while (s[*i] && (s[*i] != '"'))
				(*i)++;
		}
		else if (s[*i] && (s[*i] == '\''))
		{
			i++;
			while (s[*i] && (s[*i] != '\'' && s[*i - 1] != '\\'))
				(*i)++;
			if (s[*i] && s[*i - 1] == '\\')
			{
				(*i)++;
				while (s[*i] && (s[*i] != '\''))
					i++;
			}
		}
	}
}

int		count_word(char *s)
{
	int i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
			i++;
		if (!s[i])
			return (cnt);
		cnt++;
		while (s[i] && ((s[i] < 9 || s[i] > 13) && s[i] != ' '))
		{
			count_word_while(s, &i);
			i++;
		}
		if (!s[i])
			return (cnt);
	}
	return (cnt);
}

char	*fill_home(int *i, t_var *l_var)
{
	t_var	*start;
	char	*res;
	int		a;

	res = "";
	start = l_var;
	a = (*i);
	while (start->next)
	{
		if ((ft_strcmp(start->name, "HOME")) == 0)
		{
			res = ft_strdup(start->data);
			(*i)++;
			return (res);
		}
		start = start->next;
	}
	if (!start->next)
		res = ft_strdup("~");
	return (res);
}

char	*fill_simple(char *s, int *i)
{
	int		start;
	char	*res;
	int		j;

	start = ++(*i);
	j = 0;
	while (s[*i] && (s[*i] != '\'' || s[*i - 1] == '\\'))
		(*i)++;
	if (!s[*i])
	{
		ft_put("error :end the \', its not 21sh bro.", 1, RESET);
		return (NULL);
	}
	res = malloc(sizeof(char) * (*i - start + 1));
	while (start < *i)
	{
		res[j] = s[start];
		j++;
		start++;
	}
	res[j] = '\0';
	*i = start;
	return (res);
}
