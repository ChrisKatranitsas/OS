#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> 

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) { 
        close(pipe_fd[1]);
        char buffer[64] = {0}; // initialize with zeros
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; 
            printf("Child received: %s\n", buffer);
        } else {
            perror("Read failed");
        }
        close(pipe_fd[0]);
    } else { 
        close(pipe_fd[0]);
        const char *message = "Hello, child!";
        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message) + 1);
        if (bytes_written == -1) {
            perror("Write failed");
        }
        close(pipe_fd[1]); 
        wait(NULL);
    }

    return 0;
}

