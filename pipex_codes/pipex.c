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

#include "../pipex.h"

static void	second_child_process(int *pipes, char **argv, char **envp)
{
	int		fd_output;
	int		output_file_exists;

	if (!pipes || !argv || !envp)
		return ;
	output_file_exists = 0;
	if (access(argv[4], F_OK) == 0)
		output_file_exists = 1;
	fd_output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output < 0)
	{
		if (!output_file_exists)
			unlink(argv[4]);
		error("Open function error", &pipes[0], NULL);
	}
	if ((dup2(fd_output, STDOUT_FILENO)) == -1)
		error("dup2 function error", &fd_output, &pipes[0]);
	close(fd_output);
	if ((dup2(pipes[0], STDIN_FILENO)) == -1)
		error("dup2 function error", &pipes[0], NULL);
	close(pipes[0]);
	execution(argv[3], envp);
}

static void	first_child_process(int *pipes, char **argv, char **envp)
{
	int		fd_input;

	if (!pipes || !argv || !envp)
		return ;
	close(pipes[0]);
	fd_input = open(argv[1], O_RDONLY);
	if (fd_input < 0)
		error("Open function error", &pipes[1], NULL);
	if (dup2(fd_input, STDIN_FILENO) == -1)
		error("dup2 function error", &fd_input, &pipes[1]);
	close(fd_input);
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
		error("dup2 function error", &pipes[1], NULL);
	close(pipes[1]);
	execution(argv[2], envp);
}

static void	fork_loop(int *pipes, char **argv, char **envp, pid_t *pids_array)
{
	int			count;
	pid_t		pid;

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
			pids_array[count] = pid;
			close(pipes[count]);
		}
	}
}

static int	fork_execution(int *pipes, char **argv, char **envp, int *status)
{
	int			i;
	pid_t		pids_array[2];

	if (!pipes || !argv || !envp)
		return (0);
	fork_loop(pipes, argv, envp, pids_array);
	i = 1;
	while (i >= 0)
	{
		waitpid(pids_array[i], status, 0);
		i--;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			pipes[2];
	int			status;

	if (!envp || !envp[0])
		return (ft_printf("Error collecting envp variables\n"));
	if (!argv || argc != 5)
	{
		ft_printf("Error: send  args < in \"cmd1\" \"cmd2\" > out\n");
		return (EXIT_FAILURE);
	}
	if (pipe(pipes) == -1)
		error("Pipe function failure", NULL, NULL);
	if (!fork_execution(pipes, argv, envp, &status))
		return (ft_printf("Error with fork_execution"));
	status = WEXITSTATUS(status);
	return (status);
}
