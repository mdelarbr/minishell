/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_word.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 11:41:37 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/28 11:14:34 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_word(char const *s, char c)
{
	int e;
	int	cnt;

	e = 0;
	cnt = 0;
	if (s[e] != c && s[e] != '\0')
		cnt++;
	while (s[e])
	{
		if (s[e] == c && s[e + 1] != c && s[e + 1])
			cnt++;
		e++;
	}
	return (cnt);
}
