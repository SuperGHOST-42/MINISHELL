/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:03:31 by arpereir          #+#    #+#             */
/*   Updated: 2025/05/03 18:50:02 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char const *src, unsigned int size)
{
	int					src_len;
	unsigned int		i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size <= 0)
		return (src_len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
/*
int	main(void)
{
	char	str[] = "Ariclenes";
	char	str2[] = "Alexandre";

	printf("%s\n", ft_strlcpy(str, str2, ft_strlen(str2)));
	return (0);
}
*/
