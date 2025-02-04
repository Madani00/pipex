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
- save the stdin, then read from a file, then return the stdin to its state 
```bash
int main()
{
    int savein = dup(STDIN_FILENO);    // Save the current stdin (file descriptor 0) savein = 3;
    // Open a file to redirect stdin
    int fd = open("inpt.txt", O_RDONLY); // fd = 4
    // Redirect stdin to the file
    dup2(fd, STDIN_FILENO);
    close(fd); // Close the file descriptor since it's no longer needed
    char buffer[100];    // Read from the new stdin (file input)
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
        printf("Read from input.txt: %s", buffer);
    }
    if (dup2(savein, STDIN_FILENO) == -1)   // Restore the original stdin
	{
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(savein);
    printf("Enter something: "); // Read from the restored stdin (terminal input)
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("You entered: %s", buffer);
    }
}
```
---
## Dynamic Redirection Using Pipes
- **What Is a Pipe?** A pipe allows data to flow between two processes: one writes to the pipe, and the other reads from it.

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
```bash
int main()
{
	int fds[2];
	pipe(fds);
	if (fork() == 0)
	{
		int x;
		close(fds[0]);
		printf("enter something b: ");
		scanf("%d", &x);
		write(fds[1], &x, sizeof(int));
		close(fds[1]);
	}
	else
	{
		int y;
		close(fds[1]);
		read(fds[0], &y, sizeof(int));
		printf("get this from the child: %d\n", y);
		close(fds[0]);
	}
}
```
- if you remove sleep it hangs , cause the parent write and read and the same time .., solution is you must have 2 pipes 
```bash
int main()
{
	int fds[2];
	pipe(fds);
	if (fork() == 0) {
		int x;
		read(fds[0], &x, sizeof(int));
		printf("recieve from the parent : %d\n", x);

		x *= 2;
		write(fds[1], &x, sizeof(int));
		printf("child write: %d \n", x);
	}
	else {
		int y = 5;
		write(fds[1], &y, sizeof(int));
		printf("parent write: %d \n", y);
		sleep(2);
		close(fds[0]);
		read(fds[0], &y, sizeof(int));
		printf("parent gets this from the child: %d\n", y);
		wait(NULL);
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
 
---
## pipe
- pipe buffer is stored in `kernel spece`, not in `user space`. This means:
- The buffer is managed by the operating system / not directly accessible by user-space processes. / kernel handles all the details of reading from and writing to the buffer
- Pipes are blocking by default. If the buffer is empty, the reading process blocks. If the buffer is full, the writing process blocks.
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
- `access()` does NOT search $PATH. It only looks in the current directory unless you specify an absolute or relative path.
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
## while (wait(NULL) > 0)
- if you just use wait you will notice some behaviors
```bash
int main(void)
{
    int num_children = 3;
    for (int i = 0; i < num_children; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            printf("Child %d (PID: %d) started.\n", i + 1, getpid());
            sleep(i + 4);
            printf("Child %d (PID: %d) finished.\n", i + 1, getpid());
            exit(0);
        }
    }
    printf("Parent process (PID: %d) waiting for all children to finish...\n\n", getpid());
    while (wait(NULL) > 0)
        ;
    printf("Parent process (PID: %d) detected all children have finished.\n", getpid());
}
```
---
## NOTES
- **child process** can also create one or more processes (the child becomes the parent of these new processes)
- **sort** : reads input and writes output, Once the user types Ctrl-D (which closes the write end of the communication channel that connects the keyboard to the stdin of the sort process)
- After the `fork()` call, changes to the parent process will not be visible to the child process and vice versa.
- The kernel creates the very first process (either init or its modern replacement like systemd) when the system boots.
- A **program** is just a set of instructions stored on disk (like an .exe or .out file).
- A **process** is what happens when the program is loaded into memory and executed.
- returns (dup2(fds[0], 0))  <--- return the new file fd which is 0.
- **zombie process** is a child process that has terminated but still has an entry in the process table,
this happens bc the parent process has not yet called wait() to read the child's exit status
- `while (wait(NULL) > 0` ensures that the parent process waits for all child processes to finish before proceeding.
it fixes issues with `/dev/random` by ensuring that all child processes complete before the parent process terminates.
fixes `sleep` by ensuring that the parent process waits for the sleep command to finish before executing the next command.
---
## Copy-on-Write (CoW) mechanism
- After fork(), Instead of duplicating memory immediately, it shares memory between the parent and child processes. Only when one process tries to modify the memory does the OS create a separate copy for that process.
- ctrl+z  temporarily pause a process, You can resume the process using the **fg** `exit 148`
- ctrl+c stop a running process        `exit 130`
- ctrl+d   Ends input to the current process or shell.    `exit 0`

![dup](https://github.com/user-attachments/assets/53125f42-64fd-4c00-a977-dc72081adde8)
![pipe3](https://github.com/user-attachments/assets/b6b40356-6323-4b56-bf49-8f81ac9f13e5)
![simple_fork](https://github.com/user-attachments/assets/fb2ecadb-f3ab-477d-b9ba-3505a330e75b)
![sort_pipe_in_out](https://github.com/user-attachments/assets/bf3a1088-2bf0-4069-bde1-3a551c30166c)




