/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:12:13 by arpereir          #+#    #+#             */
/*   Updated: 2025/05/03 19:01:32 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	*str;
	char	*str2;

	str = memcpy(NULL, "A", 1);
	//str2 = ft_memcpy(NULL, "A", 1);
	printf("%s\n", str);
}
*/