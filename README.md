# pipex

## Dup

```bash
// A file descriptor that you make can take a value 0, 1, 2 if stdin, stdout or stderr are closed.
int main()
{
    int fd_redirect_to = open("example.txt", O_CREAT | O_WRONLY, 0644);

    close(1); // Close stdout
    int fd_duplicate = dup(fd_redirect_to); // Duplicates fd_redirect_to to fd 1

    fprintf(stderr, "fd_duplicate: %d\n", fd_duplicate); // Print to stderr
    dprintf(fd_redirect_to, "yes it is : %d \n", fd_duplicate);     // or you can do this and pass it to the file
    printf("This will go to the file!\n"); // Redirected to "file"

    return 0;
}

dup2(fd_redirect_to, STDOUT_FILENO);   // Alternatively: close(1); dup(fd);
```
---
## Dynamic Redirection Using Pipes
- **What Is a Pipe?** A pipe allows data to flow between two processes: one writes to the pipe, and the other reads from it.
-
-
-

```bash
#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefds[2];
    char buffer[100];

    // // Create a pipe: pipefds[0] = read, pipefds[1] = write.
    pipe(pipefds);

    if (fork() == 0) {
        // Child process: Redirect stdout to the pipe and write a message
        close(pipefds[0]);               // Close unused read end
        dup2(pipefds[1], STDOUT_FILENO); // Redirect stdout to the pipe
        close(pipefds[1]);               // Close write end (no longer needed after dup2)

        printf("Hello from child process!\n");
        return 0;
    } else {
        // Parent process: Read the message from the pipe
        close(pipefds[1]); // Close unused write end
        read(pipefds[0], buffer, sizeof(buffer));
        close(pipefds[0]); // Close read end after reading

        printf("Parent read: %s", buffer);
        return 0;
    }
}
```

---
## Why Use wait(NULL)?

Without `wait(NULL):`

- The parent might terminate before the child finishes reading and writing.
- This can cause **zombie processes:**
        - The child process continues to run after the parent terminates.
        - The operating system keeps an entry for the child in the process table, waiting for the parent to acknowledge its termination.
