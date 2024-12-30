#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    FILE *file = fopen("pids.txt", "w");
    if (!file) {
        perror("File open failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        fprintf(file, "Child PID: %d\n", getpid());
    } else {
        fprintf(file, "Parent PID: %d\n", getpid());
        wait(NULL);
    }

    fclose(file);
    return 0;
}
