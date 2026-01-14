#include "../includes/minishell.h"

static int	has_slash(const char *s)
{
	while (*s)
		if (*s++ == '/')
			return (1);
	return (0);
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

char	*resolve_path(char **envp, char *cmd)
{
	char	*path;
	char	**dirs;
	char	*full;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (has_slash(cmd))
		return (ft_strdup(cmd));
	path = get_envp_value(envp, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full = join_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0)
		{
			// limpa dirs
			for (int j = 0; dirs[j]; j++) free(dirs[j]);
			free(dirs);
			return (full);
		}
		free(full);
		i++;
	}
	for (int j = 0; dirs[j]; j++) free(dirs[j]);
	free(dirs);
	return (NULL);
}
