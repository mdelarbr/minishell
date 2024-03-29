/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 18:36:24 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 18:38:21 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = 0;
	k = ft_strlen(dest);
	while (dest[i] != '\0')
		i++;
	while (src[j] && i < n - 1 && n)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	if (k < n)
		return (k + ft_strlen((char *)src));
	return (n + ft_strlen((char *)src));
}
