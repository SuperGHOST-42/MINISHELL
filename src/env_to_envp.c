#include "../includes/minishell.h"

static int	should_export(t_env *node)
{
	if (!node || !node->key)
		return (0);
	if (!node->has_value)
		return (0);
	return (1);
}

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (should_export(env))
			n++;
		env = env->next;
	}
	return (n);
}

void	free_envp(char **envp)
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

	if (!node || !node->key)
		return (NULL);
	tmp = ft_strjoin(node->key, "=");
	if (!tmp)
		return (NULL);
	if (!node->value)
		return (tmp);
	line = ft_strjoin(tmp, node->value);
	free(tmp);
	return (line);
}

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
		if (should_export(env))
		{
			envp[i] = join_kv(env);
			if (!envp[i])
			{
				free_envp(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
