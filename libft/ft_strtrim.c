/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:29:56 by arpereir          #+#    #+#             */
/*   Updated: 2025/04/15 16:47:19 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*new_str;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		i++;
	}
	j = ft_strlen(s1) - 1;
	while (j > i)
	{
		if (!ft_strchr(set, s1[j]))
			break ;
		j--;
	}
	new_str = ft_substr(s1, i, j - i + 1);
	return (new_str);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("...He.llo...", "."));
	return (0);
}*/
