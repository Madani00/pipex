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
```bash
int main(int argc, char *argv[]) {
    int pipefds[2];
    char buf;

    pipe(pipefds);

    if (fork() == 0) { // Child process
        close(pipefds[1]); // Close write end of the pipe
        while (read(pipefds[0], &buf, 1) > 0) { // Read one byte at a time
            write(1, &buf, 1); // Write to stdout (1)
        }
        write(1, "\n", 1); // Add a newline for clarity
        close(pipefds[0]); // Close read end of the pipe
    } else { // Parent process
        close(pipefds[0]); // Close read end of the pipe
        write(pipefds[1], argv[1], strlen(argv[1])); // Write to the pipe
        close(pipefds[1]); // Close write end of the pipe
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}

```
---
## Why Use wait(NULL)?

Without `wait(NULL):`

- The parent might terminate before the child finishes reading and writing.
- This can cause **zombie processes:**
    - The child process continues to run after the parent terminates.
    - The operating system keeps an entry for the child in the process table, waiting for the parent to acknowledge its termination.
 
---
## pipe
```bash
int main()
{
    int pipefds[2];
    char write_msg[] = "hi madani easy does it!";
    char read_msg[20];

    pipe(pipefds); // Create a pipe

    // Write to the pipe
    write(pipefds[1], write_msg, sizeof(write_msg));

    // Read from the pipe
    read(pipefds[0], read_msg, sizeof(read_msg));

    printf("Read from pipe: %s\n", read_msg);

    return 0;
}
```
---
## fork

- show how the parent wait for the child in easy easy way possible
- changes in the child (process) does not affect other processes
```bash
int main(void)
{
	int i, pid;
	pid = getpid();
	printf("parent pid = %i\n", pid);
	pid = fork();
	if (pid == 0)
	{
		for (i = 0; i < 5; i++)
		{
			printf("child process: %i\n",i);
			sleep(1);
		}
		printf("child exiting\n");
		exit(0);
	}
	else
	{
		printf("child pid = %i\n", pid);
		printf("waiting for child\n");
		wait(NULL);
		printf("child terminated\n");
	}
	printf("parent exiting\n");
}
```
```yaml
// 2^n       <-- to get the number of outputs
int main()
{
	fork();
	fork();
	printf("how many times this line is gonna print?? \n"); // 4 times
}
```
```yaml
// to get only 3 processes
int main()
{
	int fd = fork();
	if (fd != 0)
		fork();
	printf("how many times this line is gonna print?? \n"); // 3 times
}
```
---
# execve
- `execve` it replaces the current process image with a new one, and any dynamically allocated memory in the current process (including args and envp) is no longer accessible. 
- the last line does not print, bc the memory of our program gets overwritten by the new program `ls` 
```bash
int main(int argc, char **argv)
{
	char *args[] = {"/bin/ls", "-a", 0};

	execve(args[0], args, NULL);
	perror("execve hadchi fchkl it does not print");
	exit(1);
}
```
---
## access
- you can move `ls` command to you diro ,and test this 
```bash
int main()
{
	if (access("ls", X_OK | F_OK) == 0) {
		printf("File exists.\n");
	} else {
		perror("File does not exist");
	}
}
```
---
## NOTES
- **child process** can also create one or more processes (the child becomes the parent of these new processes)
- **sort** : reads input and writes output, Once the user types Ctrl-D (which closes the write end of the communication channel that connects the keyboard to the stdin of the sort process)
- After the `fork()` call, changes to the parent process will not be visible to the child process and vice versa.
- The kernel creates the very first process (either init or its modern replacement like systemd) when the system boots.
