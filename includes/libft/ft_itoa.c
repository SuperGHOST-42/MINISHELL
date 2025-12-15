/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:38:57 by arpereir          #+#    #+#             */
/*   Updated: 2025/04/26 18:02:06 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	nb;

	nb = (long)n;
	len = count_len(nb);
	if (n < 0)
	{
		nb = -nb;
		len++;
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
		result[0] = '-';
	while (nb > 0)
	{
		result[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (result);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(INT_MAX));
	return (0);
}
*/