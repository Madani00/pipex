# pipex

## Dup
```bash
// The answer is YES. A file descriptor that you make can take a value 0, 1, 2 if stdin, stdout or stderr are closed.
close(1);     //closing stdout
newfd=dup(1); //newfd takes value of least available fd number

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
