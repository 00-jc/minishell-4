/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoria <asoria@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:53:59 by asoria            #+#    #+#             */
/*   Updated: 2026/01/12 21:05:44 by asoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_envp(char **envp, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		return (1);
	j = 0;
	while (j < i)
	{
		shell->envp[j] = ft_strdup(envp[j]);
		if (!shell->envp[j])
		{
			while (j > 0)
				free(shell->envp[--j]);
			free(shell->envp);
			return (1);
		}
		j++;
	}
	shell->envp[j] = NULL;
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
			return (free_split(paths), path);
		free(path);
		i++;
	}
	return (free_split(paths), NULL);
}

static void	init_config_file(t_shell *shell)
{
	int	fd;

	shell->config_file = ".msrc";
	fd = open(shell->config_file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		printf("Couldn't open .msrc: %s\n", strerror(errno));
	else
		close(fd);
}

static void	init_rl_history(t_shell *shell)
{
	int	fd;

	shell->history_file = ".ms_history";
	fd = open(shell->history_file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		printf("Couldn't open .ms_history: %s\n", strerror(errno));
	read_history(shell->history_file);
}

int	init_shell(char **argv, char **envp, t_shell *shell)
{
	(void)argv;
	ft_bzero(shell, sizeof(t_shell));
	shell->cmd_list = NULL;
	get_envp(envp, shell);
	init_config_file(shell);
	init_rl_history(shell);
	shell->prompt = get_prompt(shell);
	return (0);
}
