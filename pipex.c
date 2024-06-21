/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:44:28 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/06/21 16:09:46 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error_message, int *close_fd)
{
	if (!error_message)
		return ;
	if (close_fd)
		close(*close_fd);
	perror(error_message);
	exit(EXIT_FAILURE);
}

void	second_child_process(int *pipes, char **argv, char **envp)
{
	char	*commands[4];
	int		fd_output;

	if (!pipes || !argv || !envp)
		return ;
	close(pipes[1]);
	fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output < 0)
		error("Open function error", NULL);
	if ((dup2(fd_output, STDOUT_FILENO)) == -1)
		error("dup2 function error", &fd_output);
	close(fd_output);
	if ((dup2(pipes[0], STDIN_FILENO)) == -1)
		error("dup2 function error", &pipes[0]);
	close(pipes[0]);
	commands[0] = "/bin/sh";
	commands[1] = "-c";
	commands[2] = argv[3];
	commands[3] = NULL;
	execve("/bin/sh", commands, envp);
}

void	first_child_process(int *pipes, char **argv, char **envp)
{
	char	*commands[4];
	int		fd_input;

	if (!pipes || !argv || !envp)
		return ;
	close(pipes[0]);
	fd_input = open(argv[1], O_RDONLY);
	if (fd_input < 0)
		error("Open function error", NULL);
	if (dup2(fd_input, STDIN_FILENO) == -1)
		error("dup2 function error", &fd_input);
	close(fd_input);
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
		error("dup2 function error", &pipes[1]);
	close(pipes[1]);
	commands[0] = "/bin/sh";
	commands[1] = "-c";
	commands[2] = argv[2];
	commands[3] = NULL;
	execve("/bin/sh", commands, envp);
}

int	fork_execution(int *pipes, char **argv, char **envp)
{
	int			count;
	pid_t		pid;
	int			status;

	count = 2;
	while (--count >= 0)
	{
		pid = fork();
		if (pid < 0)
			error("Fork function failure", NULL);
		else if (pid == 0)
		{
			if (count == 1)
				first_child_process(pipes, argv, envp);
			else if (count == 0)
				second_child_process(pipes, argv, envp);
		}
		else
		{
			waitpid(pid, &status, 0);
			close(pipes[count]);
		}
	}
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	int			pipes[2];
	int			status;

	if (!argv || argc != 5)
		return (ft_printf("Error: expected args < in \"cmd1\" \"cmd2\" > out\n"));
	if (!envp)
		return (ft_printf("Error collecting envp variables\n"));
	if (pipe(pipes) == -1)
		error("Pipe function failure", NULL);
	status = fork_execution(pipes, argv, envp);
	status = WEXITSTATUS(status);
	return (status);
}
