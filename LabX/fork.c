#include <stdio.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            break;
        } else {
            printf("Parent process: PID = %d\n", getpid());
        }
    }
    return 0;
}
