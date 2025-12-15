/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 01:06:30 by arpereir          #+#    #+#             */
/*   Updated: 2025/04/26 17:44:20 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*occ;
	char	ch;

	occ = NULL;
	ch = (char)c;
	if (ch == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == ch)
			occ = (char *)s;
		s++;
	}
	return (occ);
}
