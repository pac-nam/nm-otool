/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 12:37:47 by tbleuse           #+#    #+#             */
/*   Updated: 2018/11/09 15:43:16 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char				*ft_rev(char *dst, char* src, int size)
{
	int				index;

	index = -1;
	while (size > 0)
		dst[++index] = src[--size];
	return (dst);
}

uint32_t			ft_rev32(uint32_t nb)
{
	char			new[4];

	return (*((uint32_t*)ft_rev(&(new[0]), (char*)(&nb), 4)));
}

uint64_t		ft_rev64(uint64_t nb)
{
	char			new[8];

	return (*((uint64_t*)ft_rev(&(new[0]), (char*)(&nb), 8)));
}

// int main(void)
// {
// 	printf("%x\n", ft_rev32(0xbabecafe));
// 	printf("%llx\n", ft_rev64(0xbabecafefeedface));
// }