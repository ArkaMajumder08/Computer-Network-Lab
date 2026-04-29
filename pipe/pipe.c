#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent process";
    char read_msg[100];

    // Create pipe
    if (pipe(fd) == -1) {
        printf("Pipe creation failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    // Parent process
    if (pid > 0) {
        close(fd[0]);  // Close read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);  // Close write end
    }

    // Child process
    else {
        close(fd[1]);  // Close write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);  // Close read end
    }

    return 0;
}
