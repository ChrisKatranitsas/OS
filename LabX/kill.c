#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sigusr1_handler(int sig) {
    printf("Child received SIGUSR1 (signal %d).\n", sig);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) { 
        if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
            perror("Signal handler registration failed");
            exit(1);
        }
        printf("Child process waiting for SIGUSR1...\n");
        pause(); 
    } else { 
        printf("Parent process sending SIGUSR1 to child (PID: %d).\n", pid);
        sleep(2); 
        kill(pid, SIGUSR1);
        wait(NULL); 
    }

    return 0;
}
