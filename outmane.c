char	*ft_check(char *str, char *path)
{
	char	**parse;
	char	*s;
	int		i;
	char	*nstr;

	i = 0 ;
	parse = ft_split(path, ':');
	if (!parse || str[0] == '/' || str[0] == '.' || !str[0])
	{
		ft_free(parse);
		return (NULL);
	}
	nstr = ft_strjoin("/", str);
	while (parse[i])
	{
		s = ft_strjoin(parse[i], nstr);
		if (access(s, X_OK) == 0)
			return (s);
		free(s);
		i++;
	}
	ft_free(parse);
	return (free(nstr), NULL);
}

void	child_cmd1(char *av, char **env)
{
	char	**str;
	char	*path;
	char	*exe;

	path = get_path(env);
	str = ft_split(av, ' ');
	if (!ft_checknull(av))
		empty_or_space("command not found : ", str);
	if (!ft_checkfirst(str[0]))
		exe = ft_check(str[0], path);
	else
		exe = ft_checkfirst(str[0]);
	if (!exe)
		ft_writefree("command not found : ", str);
	execve(exe, str, env);
	ft_writefree("i can't execute this command :", str);
}

void	execute_cmd(char *str, t_pipex strct, int i, pid_t *exit)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error(1);
	pid = fork();
	*exit = pid;
	if (pid == -1)
		error(1);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], 1) == -1)
			error(1);
		if (i == strct.ac - 2)
			if (dup2(strct.outf, 1) == -1)
				error(1);
		child_cmd1(str, strct.env);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], 0) == -1)
			ft_putstr_fd("dup2 just failed", 2);
	}
}

int	main(int ac, char **av, char **env)
{
	int		inf_or_outf[2];
	int		i;
	t_pipex	strct;
	pid_t	ext;
	int		status;

	if (ac >= 5)
	{
		if (ft_strncmp("here_doc", av[1], 8) == 0)
			inf_or_outf[0] = ft_here_doc(av[2], &i);
		else
			for_norm(inf_or_outf[0], av[1], &i);
		inf_or_outf[1] = get_fd(av[ac - 1], 1);
		strct = fill_the_struct(ac, inf_or_outf, env);
		while (++i < ac - 1)
			execute_cmd(av[i], strct, i, &ext);
		waitpid(ext, &status, 0);
		while (wait(NULL) > 0)
			;
		exit(WEXITSTATUS(status));
	}
	else
		return (ft_putstr_fd("syntax error try f1 cmd1 ... cmdn file2", 2), 1);
	return (close(inf_or_outf[0]), close(inf_or_outf[1]));
}


void	ft_writefreecmd(char *str, char **spl)
{
	ft_putstr_fd(str, 2);
	ft_free(spl);
	exit(127);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	error(int i)
{
	ft_putstr_fd("Error ", 2);
	exit(i);
}

int	get_fd(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_RDONLY);
	else if (i == 1)
		file = open(av, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (file == -1)
		error(1);
	return (file);
}

int	ft_here_doc(char *limiter, int *i)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;

	*i = 3;
	if (pipe(pipefd) == -1)
		error(1);
	pid = fork();
	if (pid == -1)
		error(1);
	if (pid == 0)
	{
		line = get_next_line(0);
		close(pipefd[0]);
		while (line)
		{
			cold_arms(line, limiter);
			write(pipefd[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
		free(line);
	}
	close(pipefd[1]);
	return (wait(NULL), dup2(pipefd[0], 0));
}

void	cold_arms(char *line, char *limiter)
{
	char	*join;

	join = ft_strjoin(limiter, "\n");
	if (ft_strncmp(join, \
			line, ft_strlen(limiter) + 1) == 0)
	{
		free(line);
		free(join);
		exit(EXIT_FAILURE);
	}
	free(join);
}

void	for_norm(int infd, char *file1, int *i)
{
	*i = 2;
	infd = get_fd(file1, 0);
	dup2(infd, 0);
}


