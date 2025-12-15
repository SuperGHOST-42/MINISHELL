/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:54:47 by arpereir          #+#    #+#             */
/*   Updated: 2025/04/24 15:53:19 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s);
	new_str = malloc (len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		new_str[j] = f(i, s[i]);
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}
/*
char	soma(unsigned int n, char c)
{
	char	temp;
	(void) n;

	temp = c;
	temp += 1;
	return (temp);
}
int	main(void)
{
	char	arr[] = "abc";
	
	char *str = ft_strmapi(arr, soma);
	
	printf("%s\n", str);

	free(str);
	return (0);
}*/
