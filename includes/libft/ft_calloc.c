/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*            
                                        +:+ +:+         +:+     */
/*   By: arpereir <arpereir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 12:57:55 by arpereir          #+#    #+#             */
/*   Updated: 2025/03/02 12:57:55 by arpereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n_memb, size_t size)
{
	void	*ptr;

	if (n_memb * size >= INT_MAX)
		return (NULL);
	if (!n_memb || !size)
		return (malloc(1));
	ptr = malloc(n_memb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, n_memb * size);
	return (ptr);
}
// int	main(void)
// {
// 	 int	*ptr;	 
// 	 ptr = ft_calloc(3, sizeof(int));
// 	 for (int i = 0; i < 3; i++)
// 	 {
// 		printf("%i\n", ptr[i]);
// 	 }
// 	 return (0);
// }
