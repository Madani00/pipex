#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>


char    *build_executable_path(char *cmd, char *path)
{
    char    *part_path;
    char    *exe;

    part_path = ft_strjoin(path, "/");
    exe = ft_strjoin(part_path, cmd);
    free(part_path);
    if (access(exe, F_OK | X_OK) == 0)
        return (exe);
    free(exe);
    return (NULL);
}

char    *find_path(char *cmd, char **ev)
{
    char    **allpaths;
    char    *exe;
    int     i;

    i = 0;
    while (ev[i])
    {
        if (ft_strnstr(ev[i], "PATH=", 5) != NULL)
            break ;
        i++;
    }
    allpaths = ft_split((ev[i] + 5), ':');
    i = 0;
    while (allpaths[i])
    {
        exe = build_executable_path(cmd, allpaths[i]);
        if (exe != NULL)
        {
            ft_clear_tab(allpaths);
            return (exe);
        }
        i++;
    }
    ft_clear_tab(allpaths);
    return (NULL);
}

void    exe(char **ev, char *av)
{
    char    **cmd;
    char    *cmd_exe;

    cmd = ft_split(av, ' ');
    cmd_exe = find_path(cmd[0], ev);
    if (cmd_exe == NULL)
    {
        perror("pipex: command not found");
        ft_putendl_fd(cmd[0], 2);
        ft_clear_tab(cmd);
        exit(EXIT_FAILURE);
    }
    if (execve(cmd_exe, cmd, ev) == -1)
    {
        perror("pipex: execution error");
        ft_putendl_fd(cmd[0], 2);
        ft_clear_tab(cmd);
        free(cmd_exe);
        exit(EXIT_FAILURE);
    }
}
