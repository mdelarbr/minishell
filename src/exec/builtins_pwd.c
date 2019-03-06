/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_pwd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 09:40:59 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 13:42:35 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../minishell.h"

void		find_or_create(t_var *use, char *str)
{
	while (use->next && (ft_strcmp(use->name, str) != 0))
		use = use->next;
	if (ft_strcmp(use->name, str) != 0)
	{
		use->next = malloc(sizeof(t_var));
		use->next->name = ft_strdup(str);
		use->next->data = getcwd(NULL, 0);
		use->next->next = NULL;
	}
	else
	{
		free(use->data);
		use->data = getcwd(NULL, 0);
	}
}

void		simple_cd(char **res, t_var *l_var)
{
	if (access(res[1], F_OK) == 0)
	{
		if ((access(res[1], X_OK)) == -1)
			ft_put("Permission denied.", 1, RESET);
		find_or_create(l_var, "OLDPWD");
		chdir(res[1]);
		find_or_create(l_var, "PWD");
	}
	else
		ft_put("No such file or directory", 1, RESET);
}
