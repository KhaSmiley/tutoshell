/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:38:22 by kboulkri          #+#    #+#             */
/*   Updated: 2024/02/28 22:24:37 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_data
{
	char			**cmds;
	char			**argv;
	char			**path;
	char			**envp;
	char			*path_i;
	char			*path_o;
	int				fd_infile;
	int				fd_outfile;
	int				tmp_fd;
	int				argc;
	int				count_tab;
	int				nb_cmb;
	int				pid[1024];
	int				pipe_fd[2];

}					t_data;

enum
{
	GREATER,
	DGREATER,
	LESS,
	DLESS,
	PIPE,
	WSPACE,
	WORD
};

// ls > a < b -R >> c | cat -e > a | > moha cat
typedef struct t_cmd
{
	char			*cmd;
	char			**args;
	char			**files;
	int				*type;
}					t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

/* minishell.c */
int					ft_tokenizer(char *token);
int					word_size(char *str, int i);
int					alloc_token(t_token **tok, char *longchev, char *str,
						int i);
int					find_token(char *str);

/* lst_utils.c */

void				print_list(t_token *lst);
t_token				*ft_lstnew(char *content, int type);
void				ft_stock(t_token **lst, t_token *new_link);
t_token				*ft_lstlast(t_token *lst);

/* syntax.c */

int					ft_syntax(t_token *tok);
int					ft_syntax_pipe(t_token *tok);
int					ft_syntax_redir(t_token *tok);
int					ft_syntax_word(t_token *tok);

/* free_tab */

void				free_tab(char **tab);
void				close_fds(t_data *data);

/* pipex.c */

void				child_process(t_data *data, int i);
int					exec_pipe(t_data *data);
void				redirection(t_data *data, int i);
void				parent_process(t_data *data, int i);

/* utils_two.c */

char				*ft_strdup_access(char *cmd);
int					ft_strlen_from(int i, char *str);
int					open_fd(t_data *data, int i);

/* utils.c */

char				*find_envp_path(char **envp);
char				**split_path(t_data *data);
char				*complete_path(t_data *data, char *cmd);
void				init_data(char *input, char **tab, char **envp,
						t_data *data);
int					ft_access(char *path);

#endif