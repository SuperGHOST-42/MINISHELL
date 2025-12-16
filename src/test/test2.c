#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int		p[2];
	pid_t	a;
	pid_t	b;

	if (pipe(p) == -1)
		return (1);

	/* Filho A: produtor -> escreve no pipe */
	a = fork();
	if (a == -1)
		return (1);
	if (a == 0)
	{
		/* stdout (1) -> ponta de escrita do pipe */
		dup2(p[1], 1);

		/* fecha FDs que já não interessam */
		close(p[0]);
		close(p[1]);

		/* executa: echo abc */
		char *argv[] = {"echo", "abc", NULL};
		execvp(argv[0], argv);

		/* só chega aqui se falhar */
		write(2, "exec echo falhou\n", 17);
		_exit(1);
	}

	/* Filho B: consumidor -> lê do pipe */
	b = fork();
	if (b == -1)
		return (1);
	if (b == 0)
	{
		/* stdin (0) <- ponta de leitura do pipe */
		dup2(p[0], 0);

		close(p[0]);
		close(p[1]);

		/* executa: wc -c  (conta bytes) */
		char *argv[] = {"wc", "-c", NULL};
		execvp(argv[0], argv);

		write(2, "exec wc falhou\n", 15);
		_exit(1);
	}

	/* Pai: não usa o pipe */
	close(p[0]);
	close(p[1]);

	waitpid(a, 0, 0);
	waitpid(b, 0, 0);
	return (0);
}
