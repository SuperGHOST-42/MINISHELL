#include "../../includes/minishell.h"

static volatile sig_atomic_t	g_sigint;

static void	handle_sigint(int signo)
{
	(void)signo;
	g_sigint = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!rl_prompt || !(rl_prompt[0] == '>' && rl_prompt[1] == ' '
			&& rl_prompt[2] == '\0'))
		rl_redisplay();
	rl_done = 1;
}

void	setup_interactive_signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_wait_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	consume_sigint(void)
{
	if (!g_sigint)
		return (0);
	g_sigint = 0;
	return (1);
}
