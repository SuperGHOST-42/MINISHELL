#include "../includes/minishell.h"

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static char	*join_kv(t_env *node)
{
	char	*tmp;
	char	*line;

	if (!node->key)
		return (NULL);
	if (!node->value)
		return (ft_strdup(node->key));
	tmp = ft_strjoin(node->key, "=");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(tmp, node->value);
	free(tmp);
	return (line);
}

/* Converte linked list -> char** para execve (tu NÃO guardas isto no shell, é temporário) */
char	**env_to_envp(t_env *env)
{
	char	**envp;
	int		i;
	int		n;

	n = env_count(env);
	envp = ft_calloc(n + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = join_kv(env);
		if (!envp[i])
		{
			free_envp(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
