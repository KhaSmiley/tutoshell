/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:43:05 by kboulkri          #+#    #+#             */
/*   Updated: 2024/03/07 20:39:38 by kboulkri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	redirection(t_data *data, int i)
{
	// if (i == 0)
	// {
	// 	fd = open_fd(data, i);
	// 	dup2(fd, 0);
	// 	close(fd);
	// }
	// if (i == (data->nb_cmb - 1))
	// {
	// 	fd = open_fd(data, i);
	// 	dup2(fd, 1);
	// 	close(fd);
	// }
	if (i != 0)
	{
		dup2(data->tmp_fd, 0);
		close(data->tmp_fd);
	}
	if (i != data->nb_cmb - 1)
		dup2(data->pipe_fd[1], 1);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

int isaredirection(char *str)
{
	if (!strcmp(str, ">"))
		return (1);
	if (!strcmp(str, ">>"))
		return (2);
	if (!strcmp(str, "<"))	
		return (3);
	if (!strcmp(str, "<<"))	
		return (4);
	return (0);
}

void	alloctoken(t_cmd *mycmd, char **tab)
{
	int	i;
	int	f;
	int	a;

	i = 0;
	f = 0;
	a = 0;
	while (tab[i])
	{
		if (isaredirection(tab[i]))
		{
			f++;
			i++;
		}
		else
			a++;
		i++;
	}
	mycmd->args = calloc(sizeof(char *), (a + 1));
	mycmd->files = calloc(sizeof(char *), (f + 1));
	mycmd->type = malloc(sizeof(int) * f);
}

void	printtoken(t_cmd mycmd)
{
	int	i;

	i = 1;
	
	if (mycmd.cmd)
		printf("CMD = [%s]\n", mycmd.cmd);
	if (mycmd.args[0])
	{
		printf("ARGS =");
		while (mycmd.args[i])
			printf("[%s]", mycmd.args[i++]);
		printf("\n");
	}
	if (mycmd.files[0])
	{
		printf("TYPE|FILES\n");
		i = 0;
		while (mycmd.files[i])
		{
			printf("[%i]\t[%s]\n", mycmd.type[i], mycmd.files[i]);
			i++;
		}
	}
}

t_cmd	tokenizer(char **tab)
{
	t_cmd	mycmd;
	int		i;
	int		f;
	int		a;

	f = 0;
	a = 0;
	i = 0;
	alloctoken(&mycmd, tab);
	i = 0;
	while (tab[i])
	{
		if (isaredirection(tab[i]))
		{
			mycmd.type[f] = isaredirection(tab[i]);
			// mycmd.type[0] = 1;
			mycmd.files[f++] = tab[i + 1];
			// mycmd.files[0] = "moha";
			i++;
		}
		else
			mycmd.args[a++] = tab[i];
		i++;
	}
	mycmd.cmd = mycmd.args[0];
	printtoken(mycmd);
	return (mycmd);
}

void	child_process(t_data *data, int i)
{
	char	**cmd;
	char	*path;
	t_cmd	mycmd;

	cmd = ft_split(data->cmds[i], ' ');
	mycmd = tokenizer(cmd);
	printf("CMD = [%s]\n", mycmd.cmd);
	redirection(data, i);
	if (!cmd)
		return (free_tab(cmd), exit(1));
	if (!cmd[0])
		return (ft_printf("\"\" command not found\n"), free_tab(cmd), exit(1));
	path = complete_path(data, mycmd.cmd);
	if (path)
		execve(path, mycmd.args, data->envp);
	return (free_tab(cmd), free(path), exit(1));
}

void	parent_process(t_data *data, int i)
{
	close(data->pipe_fd[1]);
	if (i != 0)
		close(data->tmp_fd);
	data->tmp_fd = data->pipe_fd[0];
}

int	exec_pipe(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->nb_cmb)
	{
		if (pipe(data->pipe_fd) == -1)
			return (perror("Error pipe"), 0);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (perror("Error fork"), 0);
		if (data->pid[i] == 0)
			child_process(data, i);
		else
			parent_process(data, i);
	}
	i = 0;
	while (i < data->nb_cmb)
		waitpid(data->pid[i++], &status, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int				i;
	static t_data	data = {0};
	char			*input;
	char			**tab;

	i = 0;
	(void)argc;
	(void)argv;
	(void)data;
	(void)envp;
	// ./pipex file1 cmd1 cmd2 cmd3 file2
	// tutoshell cmd1 | cmd2 | cmd3
	while (1)
	{
		input = readline("tutoshell$ ");
		if (!input)
			break ;
		add_history(input);
		if (!find_token(input))
		{
			tab = ft_split(input, '|');
			init_data(input, tab, envp, &data);
			exec_pipe(&data);
			close(data.pipe_fd[0]);	
		}
	}
	return (0);
}
