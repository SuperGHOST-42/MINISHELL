#include "../../includes/minishell.h"

static int	has_slash(const char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (1);
		s++;
	}
	return (0);
}

static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static char	*find_in_path(char **dirs, char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full = join_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*resolve_path(t_env *env, char *cmd)
{
	char	*path;
	char	**dirs;
	char	*full;

	if (!cmd || !*cmd)
		return (NULL);
	if (has_slash(cmd))
		return (ft_strdup(cmd));
	path = get_env_exec(env, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	full = find_in_path(dirs, cmd);
	free_split(dirs);
	return (full);
}
