/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mdelarbr <mdelarbr@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 19:51:12 by mdelarbr     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 17:33:43 by mdelarbr    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>
# include <signal.h>
# include "../libft/include/libft.h"

typedef struct		s_var
{
	char			*data;
	char			*name;
	struct s_var	*next;
}					t_var;

pid_t				g_pid;
# define RED	"\033[0;31m"
# define BLUE	"\033[0;34m"
# define RESET	"\033[0;37m"

# define ERR00	"\n\tTry to reflechir pour see?\n\n"
# define ERR01	"\n\ttu m'as pris pour Sifouche?\n\n"
# define ERR02	"\n\tDonne 5$ a mdelarbr pour que cela marche.\n\n"
# define ERR03	"\n\tNan, je disais que t'etais sympa\n\n"
# define ERR04	"\n\tРобот и Елиът са едно и също лице.\n\n"
# define ERR05	"\n\tYou should ctr+d yourself\n\n"
# define ERR06	"\n\tWhy your parents didn't rm-rf you earlier?\n\n"
# define ERR07	"\n\tl'erreur se trouve entre le clavier et la chaise.\n\n"
# define ERR08	"\n\tCette commande est en DLC.\n\n"
# define ERR09	"\n\tc'est toi l'erreur\n\n"
# define ERR10	"\n\tutilise tes mains pour ecrire pas tes pied!\n\n"
# define ERR11	"\n\tpersonne n'est parfait mais toi c'est chaud!\n\n"

/*
**███████████████████████████████████████████████████████████████████████████
**█									PARCING									█
**███████████████████████████████████████████████████████████████████████████
*/

/*
**███████████████████████████████████████████████████████
**█						CLEAN.C							█
**███████████████████████████████████████████████████████
*/

int					make_clean(char *buf, t_var **l_var);
char				**first_splitbis(char **res, int *tab, char *s);
char				**strsplit(char *s, t_var *l_var);
int					ft_filling(char **split, char *s, t_var *l_var);
char				*ft_filling_while(char *s, int *tab, t_var *l_var);

/*
**███████████████████████████████████████████████████████
**█					CLEAN_MAIN.C						█
**███████████████████████████████████████████████████████
*/

char				*filling_wbis(char *s, int *tab, t_var *l_var, char *res);

/*
**███████████████████████████████████████████████████████
**█					CLEAN_BIS.C							█
**███████████████████████████████████████████████████████
*/

char				*filling_simple(char *s, int *tab, char *tmp, char *res);
int					count_first(char *buf);
int					next_first(char *buf, int i);
int					nul_split(char *buf);
void				free_tab(char **res);

/*
**███████████████████████████████████████████████████████
**█					CLEAN_FIRST_SPLIT.C					█
**███████████████████████████████████████████████████████
*/

char				**first_splitbis(char **res, int *tab, char *s);
char				**first_split(char *buf);

/*
**███████████████████████████████████████████████████████
**█					FILL_DOUBLE.C						█
**███████████████████████████████████████████████████████
*/

char				*fill_double(char *s, int *i, t_var *l_var);
char				*fill_double_solve(char *s, int *tab, t_var *l_var,
					char *res);
void				if_forest(int *tab, char *s);
void				while_double(char *var, int ivar, char *res, int *tab);

/*
**███████████████████████████████████████████████████████
**█					FILL_NOTHING.C						█
**███████████████████████████████████████████████████████
*/

char				*fill_nothing(char *s, int *i, t_var *l_var);
char				*fill_nothing_solve(char *s, int *tab, t_var *l_var,
					char *res);
void				second_if_forest(int *start, char *s);
char				*fill_var(char *s, int *i, t_var *l_var);

/*
**███████████████████████████████████████████████████████
**█					COUNT_WORD.C						█
**███████████████████████████████████████████████████████
*/

int					count_word(char *s);
void				count_word_while(char *s, int *i);
char				*fill_simple(char *s, int *i);
char				*fill_home(int *i, t_var *l_var);

/*
**███████████████████████████████████████████████████████████████████████████
**█									EXEC									█
**███████████████████████████████████████████████████████████████████████████
*/

/*
**███████████████████████████████████████████████████████
**█					USE_EXECVE.C						█
**███████████████████████████████████████████████████████
*/

int					use_execve_acces(char *tmp, char **res, t_var *l_var,
					char **path);
char				*strjoin_path(char *s1, char *s2);
int					use_execve(char **res, t_var *l_var);
void				error_bis(int i);
void				choose_error(void);

/*
**███████████████████████████████████████████████████████
**█					USE_EXECVE_BIS.C					█
**███████████████████████████████████████████████████████
*/

char				*ft_join_env(char *s1, char const *s2);
char				**split_env(t_var *l_var);
int					solve_execve(char *tmp, char **res, t_var *l_var);
int					exec_path(char **res, t_var *l_var);
int					main_exec(char **res, t_var *l_var);

/*
**███████████████████████████████████████████████████████
**█						BUILTINS.C						█
**███████████████████████████████████████████████████████
*/

int					exec_echo(char **res);
int					find_builtins(char **res, t_var **l_var);
int					exec_cd(char **res, t_var *l_var);
int					exec_oldcd(t_var *l_var, t_var *save);
int					exec_solocd(t_var *l_var, t_var *save);

/*
**███████████████████████████████████████████████████████
**█					BUILTINS_ENV.C						█
**███████████████████████████████████████████████████████
*/

void				free_unset(t_var *l_var);
int					exec_unsetenv_bis(char **res, t_var *start, t_var *ndel);
int					exec_unsetenv(char **res, t_var **l_var);
int					exec_env(t_var *l_var);
int					exec_setenv(char **res, t_var *l_var);

/*
**███████████████████████████████████████████████████████
**█					BUILTINS_PWD.C						█
**███████████████████████████████████████████████████████
*/

void				find_or_create(t_var *use, char *str);
void				simple_cd(char **res, t_var *l_var);

/*
**███████████████████████████████████████████████████████████████████████████
**█									MAIN									█
**███████████████████████████████████████████████████████████████████████████
*/

/*
**███████████████████████████████████████████████████████
**█						LNK_LIST.C						█
**███████████████████████████████████████████████████████
*/

void				data_lnklist(char *env, t_var *l_var);
void				name_lnklist(char *env, t_var *l_var);
t_var				*fill_lnklist(char **env);
void				free_lnklist(t_var *l_var);

/*
**███████████████████████████████████████████████████████
**█						MAIN.C.C						█
**███████████████████████████████████████████████████████
*/

void				restart_prog(int i);
void				restart(int i);
void				ft_put_prompt(t_var *l_var, char *color);
int					main_use(t_var **l_var, char *buf);
void				ft_put(char *str, int space, char *color);
int					main(int ac, char **av, char **env);

#endif
