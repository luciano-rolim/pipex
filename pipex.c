/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:44:28 by lmeneghe          #+#    #+#             */
/*   Updated: 2024/06/21 18:26:58 by lmeneghe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <string.h>

void error2(char *error_message, int *close_fd1, int *close_fd2)
{
    if (!error_message)
        return;
    if (close_fd1)
        close(*close_fd1);
    if (close_fd2)
        close(*close_fd2);
    // Using strerror to fetch the error string and printing it
    fprintf(stderr, "%s: %s\n", error_message, strerror(errno));

    exit(EXIT_FAILURE);
}

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

void	second_child_process(int *pipes, char **argv, char **envp)
{
	char	*commands[4];
	int		fd_output;

	if (!pipes || !argv || !envp)
		return ;
	fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_output < 0)
		error("Open function error", NULL, &pipes[0]);
	if ((dup2(fd_output, STDOUT_FILENO)) == -1)
		error("dup2 function error", &fd_output, &pipes[0]);
	close(fd_output);
	if ((dup2(pipes[0], STDIN_FILENO)) == -1)
		error("dup2 function error", NULL, &pipes[0]);
	close(pipes[0]);
	commands[0] = "/bin/sh";
	commands[1] = "-c";
	commands[2] = argv[3];
	commands[3] = NULL;
	if (execve("/bin/sh", commands, envp) == -1)
		error("Execve function error", NULL, NULL);
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
	{
		// error("Open function error1", NULL, &pipes[1]);
		error2("Open function error2", NULL, &pipes[1]);
	}
	if (dup2(fd_input, STDIN_FILENO) == -1)
		error("dup2 function error", &fd_input, &pipes[1]);
	close(fd_input);
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
		error("dup2 function error", NULL, &pipes[1]);
	close(pipes[1]);
	commands[0] = "/bin/sh";
	commands[1] = "-c";
	commands[2] = argv[2];
	commands[3] = NULL;
	if (execve("/bin/sh", commands, envp) == -1)
		error("Execve function error", NULL, NULL);
}

int	fork_execution(int *pipes, char **argv, char **envp, int *status)
{
	int			count;
	pid_t		pid;

	if (!pipes || !argv || !envp)
		return (0);
	count = 2;
	while (--count >= 0)
	{
		pid = fork();
		if (pid < 0)
			error("Fork function failure", &pipes[0], &pipes[1]);
		else if (pid == 0)
		{
			if (count == 1)
				first_child_process(pipes, argv, envp);
			else if (count == 0)
				second_child_process(pipes, argv, envp);
		}
		else
		{
			waitpid(pid, status, 0);
			close(pipes[count]);
		}
/*		else if (count == 0)
		{
			waitpid(pid, &status, 0);
			close(pipes[count]);
		}  */
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			pipes[2];
	int			status;

	if (!envp)
		return (ft_printf("Error collecting envp variables\n"));
	if (!argv || argc != 5)
		return (ft_printf("Error: expected args < in \"cmd1\" \"cmd2\" > out\n"));
	if (pipe(pipes) == -1)
		error("Pipe function failure", NULL, NULL);
	if (!fork_execution(pipes, argv, envp, &status))
		return(ft_printf("Error with fork_execution"));
	status = WEXITSTATUS(status);
	
	return (status);
}
