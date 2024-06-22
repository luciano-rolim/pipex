/*#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    int i = 0;
    while (envp[i] != NULL) {
        printf("%s\n", envp[i]);
        i++;
    }
    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefds[2];  // Array to hold the two pipe (file descriptor) endpoints
    char writeMsg[] = "Hello, pipe!";  // Message to write to pipe
    char readMsg[100];  // Buffer to read message from pipe

    // Create the pipe
    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Write to the pipe
    if (write(pipefds[1], writeMsg, strlen(writeMsg) + 1) == -1) {  // Include the null terminator
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe before reading
    close(pipefds[1]);

    // Read from the pipe
    if (read(pipefds[0], readMsg, sizeof(readMsg)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Print the content read from the pipe
    printf("Read from pipe: %s\n", readMsg);

    // Close the read end of the pipe
    close(pipefds[0]);

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefds[2];
    pid_t pid;
    const char *filename = "input.txt";

    // Create a pipe
    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        // Close the read end of the pipe, not used by the child
        close(pipefds[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipefds[1], STDOUT_FILENO);
        close(pipefds[1]);

        // Execute grep
        execlp("grep", "grep", "Test", filename, (char *)NULL);
        // If execlp returns, it must have failed
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        char buffer[1024];
        int status;

        // Close the write end of the pipe, not used by the parent
        close(pipefds[1]);

        // Read from the pipe
        while (read(pipefds[0], buffer, sizeof(buffer)) > 0) {
            printf("%s", buffer);
        }

        // Close the read end of the pipe
        close(pipefds[0]);

        // Wait for the child to finish
        waitpid(pid, &status, 0);
    }

    return 0;
}
