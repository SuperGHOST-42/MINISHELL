#include "../includes/minishell.h"

/* =======================
** small utils
** ======================= */

static int	env_keyeq(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	if (ft_strcmp(a, b) == 0)
		return (1);
	return (0);
}

static t_env	*env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

static void	env_add_back(t_env **env, t_env *node)
{
	t_env	*last;

	if (!env || !node)
		return ;
	if (!*env)
	{
		*env = node;
		return ;
	}
	last = env_last(*env);
	last->next = node;
}

static t_env	*env_new_steal(char *key, char *value, int has_value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->has_value = has_value;
	node->next = NULL;
	return (node);
}

static int	env_parse_kv(const char *s, char **k, char **v, int *hv)
{
	char	*eq;
	size_t	len;

	*k = NULL;
	*v = NULL;
	*hv = 0;
	eq = ft_strchr(s, '=');
	if (!eq)
	{
		*k = ft_strdup(s);
		if (!*k)
			return (-1);
		return (0);
	}
	len = (size_t)(eq - s);
	*k = ft_substr(s, 0, len);
	if (!*k)
		return (-1);
	*v = ft_strdup(eq + 1);
	if (!*v)
		return (free(*k), *k = NULL, -1);
	*hv = 1;
	return (0);
}

static t_env	*env_find(t_env *env, const char *key)
{
	while (env)
	{
		if (env_keyeq(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/* =======================
** free
** ======================= */

void	env_free(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

/* =======================
** init
** ======================= */

t_env	*env_from_array(char **envp)
{
	t_env	*head;
	t_env	*node;
	char	*key;
	char	*value;
	int		has_value;

	head = NULL;
	while (envp && *envp)
	{
		if (env_parse_kv(*envp, &key, &value, &has_value) < 0)
			return (env_free(head), NULL);
		node = env_new_steal(key, value, has_value);
		if (!node)
			return (free(key), free(value), env_free(head), NULL);
		env_add_back(&head, node);
		envp++;
	}
	return (head);
}

/* =======================
** get / set / unset
** ======================= */

char	*env_get(t_env *env, const char *key)
{
	t_env	*node;

	node = env_find(env, key);
	if (!node)
		return (NULL);
	if (node->has_value == 0)
		return (NULL);
	return (node->value);
}

static int	env_value_set(t_env *node, const char *value, int has_value)
{
	free(node->value);
	node->value = NULL;
	node->has_value = has_value;
	if (has_value == 0)
		return (0);
	node->value = ft_strdup(value);
	if (!node->value)
		return (-1);
	return (0);
}

static t_env	*env_new_dup(const char *key, const char *value, int has_value)
{
	char	*k;
	char	*v;

	k = ft_strdup(key);
	if (!k)
		return (NULL);
	v = NULL;
	if (has_value)
	{
		v = ft_strdup(value);
		if (!v)
			return (free(k), NULL);
	}
	return (env_new_steal(k, v, has_value));
}

int	env_set(t_env **env, const char *key, const char *value, int has_value)
{
	t_env	*cur;
	t_env	*node;

	if (!env || !key || !*key)
		return (-1);
	if (has_value && !value)
		return (-1);
	cur = env_find(*env, key);
	if (cur)
		return (env_value_set(cur, value, has_value));
	node = env_new_dup(key, value, has_value);
	if (!node)
		return (-1);
	env_add_back(env, node);
	return (0);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!env || !*env || !key)
		return (0);
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (env_keyeq(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

/* =======================
** to array helpers
** ======================= */

static char	*env_join_kv(const char *k, const char *v)
{
	size_t	klen;
	size_t	vlen;
	char	*out;

	klen = ft_strlen(k);
	vlen = ft_strlen(v);
	out = (char *)malloc(klen + 1 + vlen + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, k, klen);
	out[klen] = '=';
	ft_memcpy(out + klen + 1, v, vlen);
	out[klen + 1 + vlen] = '\0';
	return (out);
}

static void	env_arr_free_partial(char **arr, size_t i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

static int	env_count_exec(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->has_value == 1)
			n++;
		env = env->next;
	}
	return (n);
}

static int	env_count_all(t_env *env)
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

/* =======================
** to envp (execve): only KEY=VALUE
** ======================= */

char	**env_to_envp(t_env *env)
{
	char	**arr;
	size_t	i;
	int		count;

	count = env_count_exec(env);
	arr = (char **)malloc(sizeof(*arr) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->has_value == 1)
		{
			arr[i] = env_join_kv(env->key, env->value);
			if (!arr[i])
				return (env_arr_free_partial(arr, i), NULL);
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

/* =======================
** to array (export/debug): includes KEY without '='
** ======================= */

char	**env_to_array_all(t_env *env)
{
	char	**arr;
	size_t	i;
	int		count;

	count = env_count_all(env);
	arr = (char **)malloc(sizeof(*arr) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->has_value == 1)
			arr[i] = env_join_kv(env->key, env->value);
		else
			arr[i] = ft_strdup(env->key);
		if (!arr[i])
			return (env_arr_free_partial(arr, i), NULL);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	env_free_envp(char **envp)
{
	size_t	i;

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
