/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:26:02 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/06/27 09:59:02 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error(char *error_message, int *close_fd1, int *close_fd2)
{
	if (!error_message)
		return ;
	if (close_fd1)
		close(*close_fd1);
	if (close_fd2)
		close(*close_fd2);
	perror(error_message);
	exit(EXIT_FAILURE);
}

int	path_exist(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_all(char *path, char **free_array)
{
	int	i;

	if (path)
		free(path);
	if (!free_array)
		return ;
	i = -1;
	while (free_array[++i])
		free(free_array[i]);
	free(free_array);
}

char	*find_path(char **envp, char *command)
{
	int		i;
	char	**possible_paths;
	char	*path;

	if (!command || !envp)
		return (NULL);
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	possible_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (possible_paths[i])
	{
		path = ft_strings_concat(possible_paths[i], "/", command);
		if (access(path, F_OK) == 0)
			break ;
		else
		{
			free(path);
			path = NULL;
			i++;
		}
	}
	free_all(NULL, possible_paths);
	return (path);
}

void	execution(char *argv, char **envp)
{
	char	**commands;
	char	*path;

	if (!argv || !envp)
		return ;
	commands = NULL;
	path = NULL;
	if (!path_exist(envp))
	{
		write(2, "Path variable does not exist inside envp\n", 42);
		exit(EXIT_FAILURE);
	}
	commands = ft_split(argv, ' ');
	path = find_path(envp, commands[0]);
	if (!path)
	{
		free_all(NULL, commands);
		write(2, "Command not found", 18);
		exit(127);
	}
	if (execve(path, commands, envp) == -1)
	{
		free_all(path, commands);
		error("Execve function error", NULL, NULL);
	}
}
